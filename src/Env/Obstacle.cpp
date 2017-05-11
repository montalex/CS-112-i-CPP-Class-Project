#include <Env/Obstacle.hpp>

bool Obstacle::isColliding(const Obstacle& other) const
{
    double dist = INFOSV_VEC2D_HPP::distance(getCenter(), other.getCenter());
    return dist <= getRadius() + other.getRadius();
}

bool Obstacle::isPointInside(const Vec2d& p) const
{
    double dist = INFOSV_VEC2D_HPP::distance(getCenter(), p);
    return dist <= getRadius();
}

bool Obstacle::operator|(Obstacle& other) const
{
    return isColliding(other);
}

bool Obstacle::operator>(Vec2d& p) const
{
    return isPointInside(p);
}

void Obstacle::drawObstacle(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 11; // light, transparent grey
    Arc arcgraphics(0, 360, getRadius(), color, getRadius());
    arcgraphics.setOrigin(getRadius(), getRadius());
    arcgraphics.setPosition(getCenter());
    targetWindow.draw(arcgraphics);
}
