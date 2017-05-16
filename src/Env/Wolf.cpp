#include <Env/Wolf.hpp>
#include <Application.hpp>
#include <Env/Visitor.hpp>

Wolf::Wolf(const Vec2d& initPos, Genome *mother, Genome *father)
    : Animal(initPos, getAppConfig().wolf_energy_initial, mother, father,
            sf::seconds(getAppConfig().wolf_reproduction_gestation_time)) {}

Wolf::~Wolf() {}

double Wolf::getStandardMaxSpeed() const
{
    if(getEnergy() < getAppConfig().wolf_energy_initial / 2.0) {
        return getAppConfig().wolf_max_speed / 2.0;
    } else {
        return getAppConfig().wolf_max_speed;
    }
}

double Wolf::getMass() const
{
    return getAppConfig().wolf_mass;
}

double Wolf::getRadius() const
{
    return getAppConfig().wolf_size / 2.0;
}

sf::Texture& Wolf::getTexture() const
{
    return getAppTexture(getAppConfig().wolf_texture);
}

double Wolf::getViewRange() const
{
    return getAppConfig().wolf_view_range;
}

double Wolf::getViewDistance() const
{
    return getAppConfig().wolf_view_distance;
}

double Wolf::getRandomWalkRadius() const
{
    return getAppConfig().wolf_random_walk_radius;
}

double Wolf::getRandomWalkDistance() const
{
    return getAppConfig().wolf_random_walk_distance;
}

double Wolf::getRandomWalkJitter() const
{
    return getAppConfig().wolf_random_walk_jitter;
}

bool Wolf::eatable(LivingEntity const* other) const
{
    return other->eatableBy(this);
}

bool Wolf::eatableBy(Wolf  const* wolf) const
{
    return false;
}

bool Wolf::eatableBy(Sheep const* sheep) const
{
    return false;
}

bool Wolf::eatableBy(Grass const* grass) const
{
    return false;
}

bool Wolf::isDead() const
{
    return getAge() > getAppConfig().wolf_longevity ||
           getEnergy() < getAppConfig().animal_min_energy;
}

void Wolf::update(sf::Time dt)
{
    Animal::update(dt);
    setEnergy(getEnergy() - (getAppConfig().animal_base_energy_consumption
                                         + getSpeedNorm() * getAppConfig().wolf_energy_loss_factor * dt.asSeconds()));
}

double Wolf::feed(LivingEntity *entity)
{
    setFeedingTime(sf::seconds(getAppConfig().animal_feed_time));
    setEnergy(getEnergy() +  getAppConfig().animal_meal_retention * entity->getEnergy());
    entity->setEnergy(0.0);
    return 0.0;
}

bool Wolf::matable(LivingEntity const* other) const
{
    return other->canMate(this);
}

bool Wolf::canMate(Wolf const* wolf) const
{
    if(wolf->isFemale()) {
        return !isFemale() && !wolf->isPregnant()
            && wolf->getEnergy() >= getAppConfig().wolf_energy_min_mating_female;
    } else {
        return isFemale() && !isPregnant()
            && wolf->getEnergy() >= getAppConfig().wolf_energy_min_mating_male;
    }
}

bool Wolf::canMate(Sheep const* sheep) const
{
    return false;
}

bool Wolf::canMate(Grass const* grass) const
{
    return false;
}

void Wolf::meet(LivingEntity* mate)
{
    mate->breed(this);
}

void Wolf::breed(Wolf* wolf)
{
    Wolf *female;
    Wolf *male;
    if(isFemale()) {
        female = this;
        male = wolf;
    } else {
        female = wolf;
        male = this;
    }

    female->setState(MATING);
    female->setDad(male->getGenome());
    female->setMatingTime(sf::seconds(getAppConfig().animal_mating_time));
    female->setPregnant(true);
    int nbBabies = uniform(getAppConfig().wolf_reproduction_min_children, getAppConfig().wolf_reproduction_max_children);
    female->setNBabies(nbBabies);
    female->setEnergy(female->getEnergy() - (getAppConfig().wolf_energy_loss_female_per_child * nbBabies));
    female->setGestationTime(sf::seconds(getAppConfig().wolf_reproduction_gestation_time));
    male->setEnergy(male->getEnergy() - getAppConfig().wolf_energy_loss_mating_male);
    male->setMatingTime(sf::seconds(getAppConfig().animal_mating_time));
    male->setState(MATING);
}

void Wolf::breed(Sheep* sheep)
{
    return;
}

void Wolf::breed(Grass* grass)
{
    return;
}

void Wolf::givingBirth()
{
    Environment *env = &getAppEnv();
    for(int i = 0; i < getNBabies(); i++) {
        Wolf *baby = new Wolf(getPosition(), getGenome(), getDad());
        env->addEntity(baby);
    }
    setPregnant(false);
    setNBabies(0);
}

void Wolf::acceptVisit(Visitor& v) {
    v.visit(this);
}

bool Wolf::isFreeToMove() const {
    return true;
}

int Wolf::getHerdId() const {
    return -1;
}
