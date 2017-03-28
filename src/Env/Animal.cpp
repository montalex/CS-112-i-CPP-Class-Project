#include <Env/Animal.hpp>

Animal::Animal(const Vec2d& initPos)
    : position(initPos), speedNorm(0.0) {
        target = Vec2d();
        direction = Vec2d(1.0, 0.0);
        virtual_target = Vec2d(1.0, 0.0);
    }

Vec2d Animal::getPosition() const {
    return this->position;
}

void Animal::setPosition(const Vec2d& newPosition) {
    Vec2d boundedPosition = newPosition;
    double maxWidth = getAppConfig().window_simulation_width;
    double maxHeight = getAppConfig().window_simulation_height;
    if(newPosition.x > maxWidth) {
        boundedPosition.x = 0;
    } else if(newPosition.x < 0) {
        boundedPosition.x = maxWidth;
    }
    if(newPosition.y > maxHeight) {
        boundedPosition.y = 0;
    } else if(newPosition.y < 0) {
        boundedPosition.y = maxHeight;
    }
    this->position = boundedPosition;
}

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

double Animal::getStandardMaxSpeed() const {
    return ANIMAL_MAX_SPEED;
}

double Animal::getMass() const {
    return ANIMAL_MASS;
}

double Animal::getRadius() const {
    return ANIMAL_RADIUS;
}

Vec2d Animal::getSpeedVector() const {
    return this->getDirection() * this->getSpeedNorm();
}

double Animal::getViewRange() const {
	return ANIMAL_VIEW_RANGE;
}

double Animal::getViewDistance() const {
	return ANIMAL_VIEW_DISTANCE;
}

double Animal::getRotation() const {
	return this->getDirection().angle();
}

void Animal::setRotation(const double& angle) {
	this->direction.rotate(angle);
};

double Animal::getRandomWalkRadius() const {
    return ANIMAL_RANDOM_WALK_RADIUS;
}

double Animal::getRandomWalkDistance() const {
    return ANIMAL_RANDOM_WALK_DISTANCE;
}

double Animal::getRandomWalkJitter() const {
    return ANIMAL_RANDOM_WALK_JITTER;
}

void Animal::update(sf::Time dt) {
    Environment env = INFOSV_APPLICATION_HPP::getAppEnv();
    std::list<Vec2d> targetsList = env.getTargetsInSightForAnimal(this);

    /* If the target list is not empty, pick one (first one) and calculate the
     * attraction force toward it. If it is empty, create a virtual target to
     * make the Animal walk randomly.
     */
    if(!targetsList.empty()) {
        this->setTarget(targetsList.front());
        this->updatePosition(dt, this->attractionForce());
    } else {
        this->updatePosition(dt, this->randomWalk());
    }
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
    std::cout << "1 : " << current_target << std::endl;
    Vec2d random_vec = Vec2d(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised() * getRandomWalkRadius();
    this->setVirtualTarget(current_target);

    std::cout << "2 : " << this->getVirtualTarget() << std::endl;
    return this->convertToGlobalCoord(this->getVirtualTarget()+ Vec2d(getRandomWalkDistance(), 0.0)) - this->getPosition();
}

void Animal::drawOn(sf::RenderTarget& targetWindow) const {
    sf::CircleShape target = buildCircle(this->getTarget(), 5.0, sf::Color(255, 0, 0));
    auto animalSprite = buildSprite(this->getPosition(), this->getRadius() * 2.0, getAppTexture("wolf-black.png"));
    animalSprite.setRotation(this->getDirection().angle() / DEG_TO_RAD);
    targetWindow.draw(animalSprite);
    targetWindow.draw(target);
    this->drawVision(targetWindow);
    this->drawVirtualTarget(targetWindow);
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
