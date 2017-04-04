#include <Env/Wolf.hpp>
#include <Application.hpp>

Wolf::Wolf(const Vec2d& initPos, Genome *mother, Genome *father)
    : Animal(initPos, getAppConfig().sheep_energy_initial, mother, father) {}

Wolf::~Wolf() {}

double Wolf::getStandardMaxSpeed() const {
    return getAppConfig().wolf_max_speed;
}

double Wolf::getMass() const {
    return getAppConfig().wolf_mass;
}

double Wolf::getRadius() const {
    return getAppConfig().wolf_size / 2.0;
}

sf::Texture& Wolf::getTexture() const {
    return getAppTexture(getAppConfig().wolf_texture);
}

double Wolf::getViewRange() const {
    return getAppConfig().wolf_view_range;
}

double Wolf::getViewDistance() const {
    return getAppConfig().wolf_view_distance;
}

double Wolf::getRandomWalkRadius() const {
    return getAppConfig().wolf_random_walk_radius;
}

double Wolf::getRandomWalkDistance() const {
    return getAppConfig().wolf_random_walk_distance;
}

double Wolf::getRandomWalkJitter() const {
    return getAppConfig().wolf_random_walk_jitter;
}
