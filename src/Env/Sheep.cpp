#include <Env/Sheep.hpp>
#include <Application.hpp>

Sheep::Sheep(const Vec2d& initPos, Genome *mother, Genome *father)
    : Animal(initPos, getAppConfig().sheep_energy_initial, mother, father) {}

Sheep::~Sheep() {}

double Sheep::getStandardMaxSpeed() const {
    return getAppConfig().sheep_max_speed;
}

double Sheep::getMass() const {
    return getAppConfig().sheep_mass;
}

double Sheep::getRadius() const {
    return getAppConfig().sheep_size / 2.0;
}

sf::Texture& Sheep::getTexture() const {
    if(this->getGenome().getColorPhenotype() == WHITE) {
        return getAppTexture(getAppConfig().sheep_texture_white);
    } else {
        return getAppTexture(getAppConfig().sheep_texture_black);
    }
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
