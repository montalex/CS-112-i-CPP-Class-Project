#include <Env/Sheep.hpp>
#include <Application.hpp>

Sheep::Sheep(const Vec2d& initPos, Genome *mother, Genome *father)
    : Animal(initPos, getAppConfig().sheep_energy_initial, mother, father) {}

Sheep::~Sheep() {}

double Sheep::getStandardMaxSpeed() const
{
    if(this->getEnergy() < getAppConfig().sheep_energy_initial / 2.0) {
        return getAppConfig().sheep_max_speed / 2.0;
    } else {
        return getAppConfig().sheep_max_speed;
    }
}

double Sheep::getMass() const
{
    return getAppConfig().sheep_mass;
}

double Sheep::getRadius() const
{
    return getAppConfig().sheep_size / 2.0;
}

sf::Texture& Sheep::getTexture() const
{
    if(this->getGenome().getColorPhenotype() == WHITE) {
        return getAppTexture(getAppConfig().sheep_texture_white);
    } else {
        return getAppTexture(getAppConfig().sheep_texture_black);
    }
}

double Sheep::getViewRange() const
{
    return getAppConfig().sheep_view_range;
}

double Sheep::getViewDistance() const
{
    return getAppConfig().sheep_view_distance;
}

double Sheep::getRandomWalkRadius() const
{
    return getAppConfig().sheep_random_walk_radius;
}

double Sheep::getRandomWalkDistance() const
{
    return getAppConfig().sheep_random_walk_distance;
}

double Sheep::getRandomWalkJitter() const
{
    return getAppConfig().sheep_random_walk_jitter;
}

bool Sheep::eatable(LivingEntity const* other) const
{
    return other->eatableBy(this);
}

bool Sheep::eatableBy(Wolf  const* wolf) const
{
    return true;
}

bool Sheep::eatableBy(Sheep const* sheep) const
{
    return false;
}

bool Sheep::eatableBy(Grass const* grass) const
{
    return false;
}

bool Sheep::isDead() const
{
    return this->getAge() > getAppConfig().sheep_longevity ||
           this->getEnergy() < getAppConfig().animal_min_energy;
}

void Sheep::update(sf::Time dt)
{
    Animal::update(dt);
    this->setEnergy(this->getEnergy() - (getAppConfig().animal_base_energy_consumption
                                         + this->getSpeedNorm() * getAppConfig().sheep_energy_loss_factor * dt.asSeconds()));
}

double Sheep::feed(LivingEntity *entity)
{
    double bite = getAppConfig().sheep_energy_bite;
    this->setEnergy(this->getEnergy() +  getAppConfig().animal_meal_retention * entity->getEnergy());
    entity->setEnergy(entity->getEnergy() - bite);
    return entity->getEnergy();
}
