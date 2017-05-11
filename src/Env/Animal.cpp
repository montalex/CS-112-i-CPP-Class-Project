#include <Env/Animal.hpp>
#include <Application.hpp>

Animal::Animal(const Vec2d& initPos, const double& startEnergy, Genome *mother,
               Genome *father, const sf::Time& gesTime) :
    LivingEntity(initPos, startEnergy), direction(Vec2d(1.0, 0.0)),
    target(Vec2d()), current_target(Vec2d(1, 0)), speedNorm(0.0), genome(mother, father), state(WANDERING),
    hungry(false), feedingTime(sf::seconds(getAppConfig().animal_feed_time)),
    matingTime(sf::seconds(0)),pregnant(false),
    nBabies(0), gestationTime(gesTime) {}

Animal::~Animal() {};

Vec2d Animal::getDirection() const
{
    return direction;
}

void Animal::setDirection(const Vec2d& newDirection)
{
    direction = newDirection;
}

Vec2d Animal::getTarget() const
{
    return target;
}

void Animal::setTarget(const Vec2d& target)
{
    this->target = target;
}

double Animal::getSpeedNorm() const
{
    return speedNorm;
}

void Animal::setSpeedNorm(const double& newNorm)
{
    speedNorm = newNorm;
}

Genome Animal::getGenome() const
{
    return genome;
}

AnimalState Animal::getState() const
{
    return state;
}

void Animal::setState(const AnimalState& newState)
{
    state = newState;
}

sf::Time Animal::getFeedingTime() const
{
    return feedingTime;
}

void Animal::setFeedingTime(const sf::Time& newTime)
{
    feedingTime = newTime;
}

sf::Time Animal::getMatingTime() const
{
    return matingTime;
}

void Animal::setMatingTime(const sf::Time& newTime)
{
    matingTime = newTime;
}

int Animal::getNBabies() const
{
    return nBabies;
}

void Animal::setNBabies(const int& nbBabies)
{
    nBabies = nbBabies;
}

sf::Time Animal::getGestationTime() const
{
    return gestationTime;
}

void Animal::setGestationTime(const sf::Time& newTime)
{
    gestationTime = newTime;
}

void Animal::updateState()
{
    Environment env = INFOSV_APPLICATION_HPP::getAppEnv();
    std::list<LivingEntity*> eatables;
    std::list<LivingEntity*> matables;
    std::list<LivingEntity*> entities = env.getEntitiesInSightForAnimal(this);
    if(isPregnant() && getGestationTime().asSeconds() <= 0) {
        setState(GIVING_BIRTH);
        return;
    }

    if(getMatingTime().asSeconds() > 0) {
        return;
    }

    if(entities.empty()) {
        setState(WANDERING);
    } else {
        for(auto entity: entities) {
            if(matable(entity) && entity->matable(this)) {
                matables.push_back(entity);
            }
            if(eatable(entity)) {
                eatables.push_back(entity);
            }
        }

        if(!isPregnant() && !matables.empty()) { /*Checks for Mates in priority if not pregnant*/
            std::cout<<"YOLO"<<std::endl;
            LivingEntity *closestEntity = getClosestEntity(matables);
            setTarget(closestEntity->getPosition());
            if(isColliding(*closestEntity)) {
                setState(MATING);
                setMatingTime(sf::seconds(getAppConfig().animal_mating_time));
                meet(closestEntity);
            } else {
                setState(MATE_IN_SIGHT);
            }
        } else if(isHungry() && !eatables.empty()) { /*If no mates checks for food if hungry */
            LivingEntity *closestEntity = getClosestEntity(eatables);
            setTarget(closestEntity->getPosition());
            if(isColliding(*closestEntity)) {
                setState(FEEDING);
                setFeedingTime(sf::seconds(getAppConfig().animal_feed_time));
                feed(closestEntity);
            } else {
                setState(FOOD_IN_SIGHT);
            }
        } else { /* If noone is interesting --> WANDERING*/
            setState(WANDERING);
        }
    }
}

double Animal::getMaxSpeed() const
{
    switch(getState()) {
    case FOOD_IN_SIGHT:
        return 3.0 * getStandardMaxSpeed();
    case MATE_IN_SIGHT:
        return 2.0 * getStandardMaxSpeed();
    case RUNNING_AWAY:
        return 4.0 * getStandardMaxSpeed();
    default:
        return getStandardMaxSpeed();
    }
}

Vec2d Animal::getSpeedVector() const
{
    return getDirection() * getSpeedNorm();
}

double Animal::getRotation() const
{
    return getDirection().angle();
}

void Animal::setRotation(const double& angle)
{
    direction.rotate(angle);
};

void Animal::update(sf::Time dt)
{
    LivingEntity::update(dt);
    if(isPregnant() && getGestationTime().asSeconds() > 0) {
        setGestationTime(getGestationTime() - dt);
    }
    updateHunger();
    updateState();
    switch(getState()) {
    case FOOD_IN_SIGHT:
    case MATE_IN_SIGHT:
        updatePosition(dt, attractionForce());
        break;
    case WANDERING:
        updatePosition(dt, randomWalk());
        break;
    case FEEDING:
        if(getFeedingTime().asSeconds() > 0) {
            setFeedingTime(getFeedingTime() - dt);
        } else {
            setState(WANDERING);
        }
    case MATING:
    if(getMatingTime().asSeconds() > 0) {
        setMatingTime(getMatingTime() - dt);
    } else {
        setState(WANDERING);
    }
    default:
        break;
    }
}

void Animal::updatePosition(sf::Time dt, const Vec2d& attractionForce)
{
    Vec2d acceleration = attractionForce / getMass();
    Vec2d newSpeedVector = getSpeedVector() + (acceleration * dt.asSeconds());
    setDirection(newSpeedVector.normalised());
    if(newSpeedVector.length() > getMaxSpeed()) {
        newSpeedVector = getDirection() * getMaxSpeed();
    }
    setSpeedNorm(newSpeedVector.length());
    setPosition(getPosition() + (newSpeedVector * dt.asSeconds()));
}

Vec2d Animal::randomWalk()
{
    Vec2d random_vec = Vec2d(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised() * getRandomWalkRadius();
    setTarget(current_target);
    return convertToGlobalCoord(getTarget() + Vec2d(getRandomWalkDistance(), 0.0)) - getPosition();
}

void Animal::drawOn(sf::RenderTarget& targetWindow) const
{
    auto animalSprite = buildSprite(getPosition(), getRadius(), getTexture());
    animalSprite.setRotation(getDirection().angle() / DEG_TO_RAD);
    targetWindow.draw(animalSprite);
    if(isDebugOn()) {
        drawVision(targetWindow);
        drawVirtualTarget(targetWindow);
        drawDebugText(targetWindow);
        Obstacle::drawObstacle(targetWindow);
    }
}

void Animal::drawVision(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    double directionRotation = getRotation();
    double viewRange = getViewRange();
    double viewDistance = getViewDistance();
    Arc arcgraphics(directionRotation - (viewRange/ DEG_TO_RAD) / 2, directionRotation + (viewRange/ DEG_TO_RAD)/2,
                    viewDistance, color, viewDistance);
    arcgraphics.setOrigin(viewDistance, viewDistance);
    arcgraphics.setPosition(getPosition());
    arcgraphics.rotate(getRotation() / DEG_TO_RAD);
    targetWindow.draw(arcgraphics);
}

void Animal::drawDebugText(sf::RenderTarget& targetWindow) const
{
    auto text = buildText(getDebugString(),
                          convertToGlobalCoord(Vec2d(150.0, 0)),
                          getAppFont(),
                          getAppConfig().default_debug_text_size,
                          sf::Color::White);
    text.setRotation(getRotation() / DEG_TO_RAD + 90);
    targetWindow.draw(text);
}

void Animal::drawVirtualTarget(sf::RenderTarget& targetWindow) const
{
    sf::CircleShape virtualRadius = buildCircle(Vec2d(0,0), getRandomWalkRadius(), sf::Color::Transparent);
    virtualRadius.setOutlineThickness(-2);
    virtualRadius.setOutlineColor(sf::Color(0, 255, 0));
    virtualRadius.setPosition(convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)));
    targetWindow.draw(virtualRadius);

    sf::CircleShape virtualTarget = buildCircle(Vec2d(0,0), 5.0, sf::Color::Blue);
    virtualTarget.setPosition(convertToGlobalCoord(getTarget()) + Vec2d(getRandomWalkDistance(), 0));
    targetWindow.draw(virtualTarget);

    sf::CircleShape direction = buildCircle(Vec2d(0,0), 5.0, sf::Color::Red);
    direction.setPosition(convertToGlobalCoord(getDirection())+ Vec2d(getRandomWalkDistance(), 0));
    targetWindow.draw(direction);
}

Vec2d Animal::attractionForce() const
{
    Vec2d toTarget = getTarget() - getPosition();
    double toTargetNorm = toTarget.length();
    if(toTargetNorm == 0.0) {
        return Vec2d(0.0, 0.0);
    }
    double coef = getDecelerationCoef(getDeceleration(toTargetNorm));
    double tempSpeed = std::min(toTargetNorm / coef, getMaxSpeed());
    Vec2d wantedSpeed = (toTarget / toTargetNorm) * tempSpeed;
    return wantedSpeed - getSpeedVector();
}

Deceleration Animal::getDeceleration(const double& distanceToTarget) const
{
    if(distanceToTarget >= SEEKING_DISTANCE_MID) {
        return STRONG;
    } else if(distanceToTarget >= SEEKING_DISTANCE_CLOSE) {
        return MIDRANGE;
    } else {
        return WEAK;
    }
}

bool Animal::isTargetInSight(const Vec2d& target) const
{
    Vec2d distanceToTarget = (target - getPosition());
    double distanceSquared = distanceToTarget.lengthSquared();

    double dotProd = getDirection().normalised().dot(distanceToTarget.normalised());
    if(dotProd < 0) {
        return false;
    }
    return isEqual(distanceSquared, 0) || (distanceSquared <= getViewDistance()*getViewDistance() &&
                                           dotProd >= cos((getViewRange() + 0.001) / 2));
}

Vec2d Animal::convertToGlobalCoord(const Vec2d& coordinates) const
{
    sf::Transform matTransform;
    matTransform.translate(getPosition());
    matTransform.rotate(getDirection().angle());
    return matTransform.transformPoint(coordinates);
}

std::string stateToString(const AnimalState state)
{
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

std::string Animal::getDebugString() const
{
    std::string sex = sexToString(getGenome().getSex());
    std::string state = stateToString(getState());
    std::string speed = to_nice_string(getSpeedNorm());
    std::string energy = to_nice_string(getEnergy());
    std::string hungry = "NOT HUNGRY";
    if(isHungry()) {
        hungry = "HUNGRY";
    }
    std::string debugStr = state + "    " + sex + "\n" + "Speed: " + speed + "\n"
                           + "Energy: " + energy + "\n" + hungry + "\n";
    return debugStr;
}

void Animal::updateHunger()
{
    if(getEnergy() < getAppConfig().animal_satiety_min ||
       (getState() == FEEDING && getEnergy() < getAppConfig().animal_satiety_max)) {
        hungry = true;
    } else {
        hungry = false;
    }
}

bool Animal::isHungry() const
{
    return hungry;
}

bool Animal::isFemale() const
{
    return getGenome().getSex() == FEMALE;
}

bool Animal::isPregnant() const
{
    return pregnant;
}

void Animal::setPregnant(const bool& preg)
{
    pregnant = preg;
}
