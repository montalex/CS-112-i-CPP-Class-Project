#include <Env/Obstacle.hpp>


Obstacle::Obstacle(Vec2d pos, double rad)
        :center(pos), rad(rad){}

Vec2d Obstacle::getCenter() {
        return center;
}

double Obstacle::getRadius() {
        return rad;
}

bool Obstacle::isColliding(const Obstacle& other) {
        double dist = INFOSV_VEC2D_HPP::distance(this->center, other.center);
        return dist <= this->rad + other.rad;
}

bool Obstacle::isPointInside(const Vec2d& p) {
        double dist = INFOSV_VEC2D_HPP::distance(this->center, p);
        return dist <= rad;
}

bool Obstacle::operator|(Obstacle& other) {
        return this->isColliding(other);
}

bool Obstacle::operator>(Vec2d& p) {
        return this->isPointInside(p);
}
