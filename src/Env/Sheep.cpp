#include <Env/Sheep.hpp>
#include <Application.hpp>

double Sheep::getStandardMaxSpeed() const {
    return getAppConfig().sheep_max_speed;
}

double Sheep::getMass() const {
    return getAppConfig().sheep_mass;
}

double Sheep::getRadius() const {
    return getAppConfig().sheep_size / 2.0;
}

double Sheep::getViewRange() const {
    return getAppConfig().sheep_view_range;
}

double Sheep::getViewDistance() const {
    return getAppConfig().sheep_view_distance;
}

double Sheep::getRandomWalkRadius() const {
    return getAppConfig().sheep_random_walk_radius;
}

double Sheep::getRandomWalkDistance() const {
    return getAppConfig().sheep_random_walk_distance;
}

double Sheep::getRandomWalkJitter() const {
    return getAppConfig().sheep_random_walk_jitter;
}
