#include <Env/Obstacle.hpp>

bool Obstacle::isColliding(const Obstacle& other) const
{
    double dist = INFOSV_VEC2D_HPP::distance(this->getCenter(), other.getCenter());
    return dist <= this->getRadius() + other.getRadius();
}

bool Obstacle::isPointInside(const Vec2d& p) const
{
    double dist = INFOSV_VEC2D_HPP::distance(this->getCenter(), p);
    return dist <= this->getRadius();
}

bool Obstacle::operator|(Obstacle& other) const
{
    return this->isColliding(other);
}

bool Obstacle::operator>(Vec2d& p) const
{
    return this->isPointInside(p);
}

void Obstacle::drawObstacle(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 11; // light, transparent grey
    Arc arcgraphics(0, 360, this->getRadius(), color, this->getRadius());
    arcgraphics.setOrigin(this->getRadius(), this->getRadius());
    arcgraphics.setPosition(this->getCenter());
    targetWindow.draw(arcgraphics);
}
