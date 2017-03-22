#include <Env/SeekingAutomaton.hpp>

SeekingAutomaton::SeekingAutomaton(const Vec2d& initPos)
                : position(initPos), speedNorm(0.0) {
                        target = Vec2d();
                        direction = Vec2d(1.0, 0.0);
                }

double SeekingAutomaton::getStandardMaxSpeed() const {
        return SEEKING_AUTOMATON_MAX_SPEED;
}

double SeekingAutomaton::getMass() const {
        return SEEKING_AUTOMATON_MASS;
}

double SeekingAutomaton::getRadius() const {
        return SEEKING_AUTOMATON_RADIUS;
}

void SeekingAutomaton::setTargetPosition(const Vec2d& target) {
        this->target = target;
}

Vec2d SeekingAutomaton::getSpeedVector() const {
        return this->direction * this->speedNorm;
}

void SeekingAutomaton::update(sf::Time dt) {
        Vec2d acceleration = this->attractionForce() / this->getMass();
        Vec2d newSpeedVector = this->getSpeedVector() + (acceleration * dt.asSeconds());
        this->direction = newSpeedVector.normalised();
        if(newSpeedVector.length() > this->getStandardMaxSpeed()) {
                newSpeedVector = this->direction * this->getStandardMaxSpeed();
        }
        this->speedNorm = newSpeedVector.length();
        this->position = this->position + (newSpeedVector * dt.asSeconds());
}

void SeekingAutomaton::drawOn(sf::RenderTarget& targetWindow) const {
        sf::CircleShape target = buildCircle(this->target, 5.0, sf::Color(255, 0, 0));
        sf::CircleShape automate = buildCircle(this->position, 15.0, sf::Color(0, 0, 255));
        targetWindow.draw(target);
        targetWindow.draw(automate);
}

Vec2d SeekingAutomaton::attractionForce() const {
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

Deceleration SeekingAutomaton::getDeceleration(const double& distanceToTarget) const {
        if(distanceToTarget >= SEEKING_DISTANCE_MID) {
                return STRONG;
        } else if(distanceToTarget >= SEEKING_DISTANCE_CLOSE) {
                return MIDRANGE;
        } else {
                return WEAK;
        }
}
