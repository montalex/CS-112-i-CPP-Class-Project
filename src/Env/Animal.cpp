#include <Env/Animal.hpp>

Animal::Animal(const Vec2d& initPos)
    : position(initPos), speedNorm(0.0) {
        target = Vec2d();
        direction = Vec2d(1.0, 0.0);
    }

Vec2d Animal::getPosition() const {
    return this->position;
}

Vec2d Animal::getDirection() const {
    return this->direction;
}

Vec2d Animal::getTarget() const {
    return this->target;
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

void Animal::setTargetPosition(const Vec2d& target) {
    this->target = target;
}

Vec2d Animal::getSpeedVector() const {
    return this->getDirection() * this->speedNorm;
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

void Animal::update(sf::Time dt) {
    Environment env = INFOSV_APPLICATION_HPP::getAppEnv();
    std::list<Vec2d> targetsList = env.getTargetsInSightForAnimal(this);
    if(!targetsList.empty()) {
        this->setTargetPosition(targetsList.front());
        Vec2d acceleration = this->attractionForce() / this->getMass();
        Vec2d newSpeedVector = this->getSpeedVector() + (acceleration * dt.asSeconds());
        this->direction = newSpeedVector.normalised();
        if(newSpeedVector.length() > this->getStandardMaxSpeed()) {
            newSpeedVector = this->getDirection() * this->getStandardMaxSpeed();
        }
        this->speedNorm = newSpeedVector.length();
        this->position = this->getPosition() + (newSpeedVector * dt.asSeconds());
    }
}

void Animal::drawOn(sf::RenderTarget& targetWindow) const {
    sf::CircleShape target = buildCircle(this->getTarget(), 5.0, sf::Color(255, 0, 0));
    sf::CircleShape animal = buildCircle(this->getPosition(), 15.0, sf::Color(0, 0, 255));
    targetWindow.draw(target);
    targetWindow.draw(animal);
    this->drawVision(targetWindow);
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
