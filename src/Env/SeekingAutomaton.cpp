#include <Env/SeekingAutomaton.hpp>

SeekingAutomaton::SeekingAutomaton(const Vec2d& initPos)
    : position(initPos), direction(Vec2d(1.0, 0.0)), target(Vec2d()), speedNorm(0.0) {}

double SeekingAutomaton::getStandardMaxSpeed() const
{
    return SEEKING_AUTOMATON_MAX_SPEED;
}

double SeekingAutomaton::getMass() const
{
    return SEEKING_AUTOMATON_MASS;
}

double SeekingAutomaton::getRadius() const
{
    return SEEKING_AUTOMATON_RADIUS;
}

void SeekingAutomaton::setTargetPosition(const Vec2d& target)
{
    this->target = target;
}

Vec2d SeekingAutomaton::getSpeedVector() const
{
    return direction * speedNorm;
}

void SeekingAutomaton::update(sf::Time dt)
{
    Vec2d acceleration = attractionForce() / getMass();
    Vec2d newSpeedVector = getSpeedVector() + (acceleration * dt.asSeconds());
    direction = newSpeedVector.normalised();
    if(newSpeedVector.length() > getStandardMaxSpeed()) {
        newSpeedVector = direction * getStandardMaxSpeed();
    }
    speedNorm = newSpeedVector.length();
    position = position + (newSpeedVector * dt.asSeconds());
}

void SeekingAutomaton::drawOn(sf::RenderTarget& targetWindow) const
{
    sf::CircleShape target_circle = buildCircle(target, 5.0, sf::Color(255, 0, 0));
    sf::CircleShape automate = buildCircle(position, 15.0, sf::Color(0, 0, 255));
    targetWindow.draw(target_circle);
    targetWindow.draw(automate);
}

Vec2d SeekingAutomaton::attractionForce() const
{
    Vec2d toTarget = target - position;
    double toTargetNorm = toTarget.length();
    if(toTargetNorm == 0.0) {
        return Vec2d(0.0, 0.0);
    }
    double coef = getDecelerationCoef(getDeceleration(toTargetNorm));
    double tempSpeed = std::min(toTargetNorm / coef, getStandardMaxSpeed());
    Vec2d wantedSpeed = (toTarget / toTargetNorm) * tempSpeed;
    return wantedSpeed - getSpeedVector();
}

Deceleration SeekingAutomaton::getDeceleration(const double& distanceToTarget) const
{
    if(distanceToTarget >= SEEKING_DISTANCE_MID) {
        return STRONG;
    } else if(distanceToTarget >= SEEKING_DISTANCE_CLOSE) {
        return MIDRANGE;
    } else {
        return WEAK;
    }
}
