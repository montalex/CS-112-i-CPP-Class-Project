#include <Env/Animal.hpp>
#include <Application.hpp>

Animal::Animal(const Vec2d& initPos, const double& startEnergy,Genome *mother, Genome *father)
    : LivingEntity(initPos, startEnergy), direction(Vec2d(1.0, 0.0)), target(Vec2d()),
    virtual_target(Vec2d(1.0, 0.0)), speedNorm(0.0), genome(mother, father) {}

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

Vec2d Animal::getVirtualTarget() const {
    return this->virtual_target;
}

void Animal::setVirtualTarget(const Vec2d& target) {
    this->virtual_target = target;
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
    // Environment env = INFOSV_APPLICATION_HPP::getAppEnv();
    // std::list<Vec2d> targetsList = env.getTargetsInSightForAnimal(this);
    //
    // /* If the target list is not empty, pick one (first one) and calculate the
    //  * attraction force toward it. If it is empty, create a virtual target to
    //  * make the Animal walk randomly.
    //  */
    // if(!targetsList.empty()) {
    //     this->setTarget(targetsList.front());
    //     this->updatePosition(dt, this->attractionForce());
    // } else {
    //     this->updatePosition(dt, this->randomWalk());
    // }
}

void Animal::updatePosition(sf::Time dt, const Vec2d& attractionForce) {
    Vec2d acceleration = attractionForce / this->getMass();
    Vec2d newSpeedVector = this->getSpeedVector() + (acceleration * dt.asSeconds());
    this->setDirection(newSpeedVector.normalised());
    if(newSpeedVector.length() > this->getStandardMaxSpeed()) {
        newSpeedVector = this->getDirection() * this->getStandardMaxSpeed();
    }
    this->setSpeedNorm(newSpeedVector.length());
    this->setPosition(this->getPosition() + (newSpeedVector * dt.asSeconds()));
}

Vec2d Animal::randomWalk() {
    Vec2d current_target = this->getVirtualTarget();
    Vec2d random_vec = Vec2d(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised() * getRandomWalkRadius();
    this->setVirtualTarget(current_target);
    return this->convertToGlobalCoord(this->getVirtualTarget()+ Vec2d(getRandomWalkDistance(), 0.0)) - this->getPosition();
}

void Animal::drawOn(sf::RenderTarget& targetWindow) const {
    sf::CircleShape target = buildCircle(this->getTarget(), 5.0, sf::Color(255, 0, 0));
    auto animalSprite = buildSprite(this->getPosition(), this->getRadius(), this->getTexture());
    animalSprite.setRotation(this->getDirection().angle() / DEG_TO_RAD);
    targetWindow.draw(animalSprite);
    targetWindow.draw(target);
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
}

void Animal::drawVirtualTarget(sf::RenderTarget& targetWindow) const {
    sf::CircleShape virtualRadius = buildCircle(Vec2d(0,0), this->getRandomWalkRadius(), sf::Color::Transparent);
    virtualRadius.setOutlineThickness(-2);
    virtualRadius.setOutlineColor(sf::Color(0, 255, 0));
    virtualRadius.setPosition(this->convertToGlobalCoord(Vec2d(this->getRandomWalkDistance(), 0)));
    targetWindow.draw(virtualRadius);

    sf::CircleShape virtualTarget = buildCircle(Vec2d(0,0), 5.0, sf::Color::Blue);
    virtualTarget.setPosition(this->convertToGlobalCoord(this->getVirtualTarget()) + Vec2d(this->getRandomWalkDistance(), 0));
    targetWindow.draw(virtualTarget);
}

Vec2d Animal::attractionForce() const {
    Vec2d toTarget = this->getTarget() - this->getPosition();
    double toTargetNorm = toTarget.length();
    if(toTargetNorm == 0.0) {
        return Vec2d(0.0, 0.0);
    }
    double coef = getDecelerationCoef(this->getDeceleration(toTargetNorm));
    double tempSpeed = std::min(toTargetNorm / coef, this->getStandardMaxSpeed());
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
