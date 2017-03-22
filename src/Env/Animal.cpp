#include <Env/Animal.hpp>

Animal::Animal(const Vec2d& initPos)
                : position(initPos), speedNorm(0.0) {
                        target = Vec2d();
                        direction = Vec2d(1.0, 0.0);
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
        return this->direction * this->speedNorm;
}

double Animal::getViewRange() const {
		return ANIMAL_VIEW_RANGE;
}

double Animal::getViewDistance() const {
		return ANIMAL_VIEW_DISTANCE;
}

double Animal::getRotation() const {
		return this->direction.angle();
}

void Animal::setRotation(const double& angle) {
		this->direction.rotate(angle);
};

void Animal::update(sf::Time dt) {
        Vec2d acceleration = this->attractionForce() / this->getMass();
        Vec2d newSpeedVector = this->getSpeedVector() + (acceleration * dt.asSeconds());
        this->direction = newSpeedVector.normalised();
        if(newSpeedVector.length() > this->getStandardMaxSpeed()) {
                newSpeedVector = this->direction * this->getStandardMaxSpeed();
        }
        this->speedNorm = newSpeedVector.length();
        this->position = this->position + (newSpeedVector * dt.asSeconds());
}

void Animal::drawOn(sf::RenderTarget& targetWindow) const {
        sf::CircleShape target = buildCircle(this->target, 5.0, sf::Color(255, 0, 0));
        sf::CircleShape animal = buildCircle(this->position, 15.0, sf::Color(0, 0, 255));
        targetWindow.draw(target);
        targetWindow.draw(animal);
        this->drawVision(targetWindow);
}

void Animal::drawVision(sf::RenderTarget& targetWindow) const {
		sf::Color color = sf::Color::Black;
	    //color.a = 16; // light, transparent grey
	    Arc arcgraphics(45, 135, this->getViewRange(), color, this->getViewDistance());
	    arcgraphics.setOrigin(this->getViewRange(), this->getViewRange());
	    arcgraphics.setPosition(arcgraphics.getOrigin());
	    arcgraphics.rotate(this->getRotation() / DEG_TO_RAD);
	    targetWindow.draw(arcgraphics);
}

Vec2d Animal::attractionForce() const {
        Vec2d toTarget = this->target - this->position;
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

