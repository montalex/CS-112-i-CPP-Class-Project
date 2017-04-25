#include <Env/Animal.hpp>
#include <Application.hpp>

Animal::Animal(const Vec2d& initPos, const double& startEnergy, Genome *mother,
                Genome *father) :
    LivingEntity(initPos, startEnergy), direction(Vec2d(1.0, 0.0)),
    target(Vec2d()), speedNorm(0.0),
    genome(mother, father), state(WANDERING) {}

Animal::~Animal() {};

Vec2d Animal::getDirection() const {
    return this->direction;
}

void Animal::setDirection(const Vec2d& newDirection) {
    this->direction = newDirection;
}

Vec2d Animal::getTarget() const {
    return this->target;
}

void Animal::setTarget(const Vec2d& target) {
    this->target = target;
}

double Animal::getSpeedNorm() const {
    return this->speedNorm;
}

void Animal::setSpeedNorm(const double& newNorm) {
    this->speedNorm = newNorm;
}

Genome Animal::getGenome() const {
    return this->genome;
}

AnimalState Animal::getState() const {
    return this->state;
}

void Animal::setState(const AnimalState& newState) {
    this->state = newState;
}

void Animal::updateState() {
    Environment env = INFOSV_APPLICATION_HPP::getAppEnv();
    std::list<LivingEntity*> eatables;
    std::list<LivingEntity*> entities = env.getEntitiesInSightForAnimal(this);
    if(entities.empty()) {
        this->setState(WANDERING);
    } else {
        for(auto entity: entities) {
            if(this->eatable(entity)) {
                eatables.push_back(entity);
            }
        }
        if(!eatables.empty()) {
            this->setState(FOOD_IN_SIGHT);
            this->setTarget(getClosestEntity(eatables)->getPosition());
        }
    }
}

double Animal::getMaxSpeed() const {
    switch(this->getState()) {
        case FOOD_IN_SIGHT:
            return 3.0 * this->getStandardMaxSpeed();
        case MATE_IN_SIGHT:
            return 2.0 * this->getStandardMaxSpeed();
        case RUNNING_AWAY:
            return 4.0 * this->getStandardMaxSpeed();
        default:
            return getStandardMaxSpeed();
    }
}

Vec2d Animal::getSpeedVector() const {
    return this->getDirection() * this->getSpeedNorm();
}

double Animal::getRotation() const {
	return this->getDirection().angle();
}

void Animal::setRotation(const double& angle) {
	this->direction.rotate(angle);
};

void Animal::update(sf::Time dt) {
    LivingEntity::update(dt);
    this->updateState();
    switch(this->getState()) {
        case FOOD_IN_SIGHT:
            this->updatePosition(dt, this->attractionForce());
            break;
        case WANDERING:
            this->updatePosition(dt, this->randomWalk());
            break;
        default:
            break;
    }
}

void Animal::updatePosition(sf::Time dt, const Vec2d& attractionForce) {
    Vec2d acceleration = attractionForce / this->getMass();
    Vec2d newSpeedVector = this->getSpeedVector() + (acceleration * dt.asSeconds());
    this->setDirection(newSpeedVector.normalised());
    if(newSpeedVector.length() > this->getMaxSpeed()) {
        newSpeedVector = this->getDirection() * this->getMaxSpeed();
    }
    this->setSpeedNorm(newSpeedVector.length());
    this->setPosition(this->getPosition() + (newSpeedVector * dt.asSeconds()));
}

Vec2d Animal::randomWalk() {
    Vec2d random_vec = Vec2d(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    Vec2d current_target = this->getTarget() + random_vec * this->getRandomWalkJitter();
    current_target = current_target.normalised() * this->getRandomWalkRadius();
    this->setTarget(current_target);
    return this->convertToGlobalCoord(this->getTarget() + Vec2d(getRandomWalkDistance(), 0.0)) - this->getPosition();
}

void Animal::drawOn(sf::RenderTarget& targetWindow) const {
    auto animalSprite = buildSprite(this->getPosition(), this->getRadius(), this->getTexture());
    animalSprite.setRotation(this->getDirection().angle() / DEG_TO_RAD);
    targetWindow.draw(animalSprite);
    if(isDebugOn()) {
        this->drawVision(targetWindow);
        this->drawVirtualTarget(targetWindow);
    }
}

void Animal::drawVision(sf::RenderTarget& targetWindow) const {
	sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    double directionRotation = this->getRotation();
    double viewRange = this->getViewRange();
    double viewDistance = this->getViewDistance();
    Arc arcgraphics(directionRotation - (viewRange/ DEG_TO_RAD) / 2, directionRotation + (viewRange/ DEG_TO_RAD)/2,
                    viewDistance, color, viewDistance);
    arcgraphics.setOrigin(viewDistance, viewDistance);
    arcgraphics.setPosition(this->getPosition());
    arcgraphics.rotate(this->getRotation() / DEG_TO_RAD);
    targetWindow.draw(arcgraphics);


    auto text = buildText(this->getDebugString(),
                          convertToGlobalCoord(Vec2d(150.0, 0)),
                          getAppFont(),
                          getAppConfig().default_debug_text_size,
                          sf::Color::White);
    text.setRotation(this->getRotation() / DEG_TO_RAD + 90); // si nécessaire
    targetWindow.draw(text);
}

void Animal::drawVirtualTarget(sf::RenderTarget& targetWindow) const {
    sf::CircleShape virtualRadius = buildCircle(Vec2d(0,0), this->getRandomWalkRadius(), sf::Color::Transparent);
    virtualRadius.setOutlineThickness(-2);
    virtualRadius.setOutlineColor(sf::Color(0, 255, 0));
    virtualRadius.setPosition(this->convertToGlobalCoord(Vec2d(this->getRandomWalkDistance(), 0)));
    targetWindow.draw(virtualRadius);

    sf::CircleShape virtualTarget = buildCircle(Vec2d(0,0), 5.0, sf::Color::Blue);
    virtualTarget.setPosition(this->convertToGlobalCoord(this->getTarget()) + Vec2d(this->getRandomWalkDistance(), 0));
    targetWindow.draw(virtualTarget);
}

Vec2d Animal::attractionForce() const {
    Vec2d toTarget = this->getTarget() - this->getPosition();
    double toTargetNorm = toTarget.length();
    if(toTargetNorm == 0.0) {
        return Vec2d(0.0, 0.0);
    }
    double coef = getDecelerationCoef(this->getDeceleration(toTargetNorm));
    double tempSpeed = std::min(toTargetNorm / coef, this->getMaxSpeed());
    Vec2d wantedSpeed = (toTarget / toTargetNorm) * tempSpeed;
    return wantedSpeed - this->getSpeedVector();
}

Deceleration Animal::getDeceleration(const double& distanceToTarget) const {
    if(distanceToTarget >= SEEKING_DISTANCE_MID) {
        return STRONG;
    } else if(distanceToTarget >= SEEKING_DISTANCE_CLOSE) {
        return MIDRANGE;
    } else {
        return WEAK;
    }
}

bool Animal::isTargetInSight(const Vec2d& target) const {
    Vec2d distanceToTarget = (target - this->getPosition());
    double distanceSquared = distanceToTarget.lengthSquared();

    double dotProd = this->getDirection().normalised().dot(distanceToTarget.normalised());
    if(dotProd < 0) {
        return false;
    }
    return isEqual(distanceSquared, 0) || (distanceSquared <= this->getViewDistance()*this->getViewDistance() &&
            dotProd >= cos((this->getViewRange() + 0.001) / 2));
}

Vec2d Animal::convertToGlobalCoord(const Vec2d& coordinates) const {
    sf::Transform matTransform;
    matTransform.translate(this->getPosition());
    matTransform.rotate(this->getDirection().angle());
    return matTransform.transformPoint(coordinates);
}

std::string stateToString(const AnimalState state) {
    switch(state) {
        case FOOD_IN_SIGHT:
            return "FOOD IN SIGHT";
        case FEEDING:
            return "FEEDING";
        case RUNNING_AWAY:
            return "RUNNING AWAY";
        case MATE_IN_SIGHT:
            return "MATE IN SIGHT";
        case MATING:
            return "MATING";
        case GIVING_BIRTH:
            return "GIVING BIRTH";
        case WANDERING:
            return "WANDERING";
        case IDLE:
            return "IDLE";
        default:
            return "---";
    }
}

std::string Animal::getDebugString() const {
    std::string sex = sexToString(this->getGenome().getSex());
    std::string state = stateToString(this->getState());
    std::string speed = to_nice_string(this->getSpeedNorm());
    std::string energy = to_nice_string(this->getEnergy());
    std::string debugStr = state + "    " + sex + "\n" + "Speed: " + speed + "\n"
                            + "Energy: " + energy + "\n";
    return debugStr;
}
