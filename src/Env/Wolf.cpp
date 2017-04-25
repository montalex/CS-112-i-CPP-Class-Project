#include <Env/Wolf.hpp>
#include <Application.hpp>

Wolf::Wolf(const Vec2d& initPos, Genome *mother, Genome *father)
    : Animal(initPos, getAppConfig().sheep_energy_initial, mother, father) {}

Wolf::~Wolf() {}

double Wolf::getStandardMaxSpeed() const {
    if(this->getEnergy() < getAppConfig().wolf_energy_initial / 2.0) {
        return getAppConfig().wolf_max_speed / 2.0;
    } else {
        return getAppConfig().wolf_max_speed;
    }
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

bool Wolf::eatable(LivingEntity const* other) const {
    return other->eatableBy(this);
}

bool Wolf::eatableBy(Wolf  const* wolf) const {
    return false;
}

bool Wolf::eatableBy(Sheep const* sheep) const {
    return false;
}

bool Wolf::eatableBy(Grass const* grass) const {
    return false;
}

bool Wolf::isDead() const {
    return this->getAge() > getAppConfig().wolf_longevity ||
            this->getEnergy() < getAppConfig().animal_min_energy;
}

void Wolf::update(sf::Time dt) {
    Animal::update(dt);
    this->setEnergy(this->getEnergy() - (getAppConfig().animal_base_energy_consumption
                    + this->getSpeedNorm() * getAppConfig().wolf_energy_loss_factor * dt.asSeconds()));
}
