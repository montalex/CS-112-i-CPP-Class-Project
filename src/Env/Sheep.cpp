#include <Env/Sheep.hpp>
#include <Application.hpp>
#include <Interface/Visitor.hpp>
Sheep::Sheep(const Vec2d& initPos, int herd, Genome *mother, Genome *father)
    : Animal(initPos, getAppConfig().sheep_energy_initial, mother, father,
             sf::seconds(getAppConfig().sheep_reproduction_gestation_time)), herdId(herd)
{
    if (herdId != -1) {
        getAppEnv().addToHerd(this);
    }
}

Sheep::~Sheep() {}

double Sheep::getStandardMaxSpeed() const
{
    if(getEnergy() < getAppConfig().sheep_energy_initial / 2.0) {
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
    if(getGenome()->getColorPhenotype() == WHITE) {
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
    return Animal::isDead() || getAge() > getAppConfig().sheep_longevity;
}

void Sheep::update(sf::Time dt)
{
    Animal::update(dt);
    setEnergy(getEnergy() - (getAppConfig().animal_base_energy_consumption
                             + getSpeedNorm() * getAppConfig().sheep_energy_loss_factor * dt.asSeconds()));
}

double Sheep::feed(LivingEntity *entity)
{
    setFeedingTime(sf::seconds(getAppConfig().animal_feed_time));
    double bite = getAppConfig().sheep_energy_bite;
    setEnergy(getEnergy() +  getAppConfig().animal_meal_retention * entity->getEnergy());
    entity->setEnergy(entity->getEnergy() - bite);
    return entity->getEnergy();
}

bool Sheep::matable(LivingEntity const* other) const
{
    return other->canMate(this);
}

bool Sheep::canMate(Wolf const* wolf) const
{
    return false;
}

bool Sheep::canMate(Sheep const* sheep) const
{
    if(sheep->isFemale()) {
        return !isFemale() && !sheep->isPregnant()
               && sheep->getEnergy() >= getAppConfig().sheep_energy_min_mating_female;
    } else {
        return isFemale() && !isPregnant()
               && sheep->getEnergy() >= getAppConfig().sheep_energy_min_mating_male;
    }
}

bool Sheep::canMate(Grass const* grass) const
{
    return false;
}

void Sheep::meet(LivingEntity* mate)
{
    mate->breed(this);
}

void Sheep::drawOn(sf::RenderTarget& targetWindow) const
{
    Animal::drawOn(targetWindow);
    if (isLeader()) {
        auto leaderSprite = buildSprite(getPosition() + Vec2d(getRadius() / 2, -getRadius() / 2),
                                        getRadius() / 2,
                                        getAppTexture(getAppConfig().animal_texture_leader));
        targetWindow.draw(leaderSprite);
    }
}

void Sheep::breed(Wolf* wolf)
{
    return;
}

void Sheep::breed(Sheep* sheep)
{
    Sheep *female;
    Sheep *male;
    if(isFemale()) {
        female = this;
        male = sheep;
    } else {
        female = sheep;
        male = this;
    }

    female->setState(MATING);
    female->setDad(male->getGenome());
    female->setMatingTime(sf::seconds(getAppConfig().animal_mating_time));
    female->setPregnant(true);
    int nbBabies = uniform(getAppConfig().sheep_reproduction_min_children, getAppConfig().sheep_reproduction_max_children);
    female->setNBabies(nbBabies);
    female->setEnergy(female->getEnergy() - (getAppConfig().sheep_energy_loss_female_per_child * nbBabies));
    female->setGestationTime(sf::seconds(getAppConfig().sheep_reproduction_gestation_time));
    male->setEnergy(male->getEnergy() - getAppConfig().sheep_energy_loss_mating_male);
    male->setState(MATING);
    male->setMatingTime(sf::seconds(getAppConfig().animal_mating_time));
}


void Sheep::breed(Grass* grass)
{
    return;
}

void Sheep::givingBirth()
{
    Environment *env = &getAppEnv();
    for(int i = 0; i < getNBabies(); i++) {
        Sheep *baby = new Sheep(getPosition(), getHerdId(), getGenome(), getDad());
        env->addEntity(baby);
    }
    setPregnant(false);
    setNBabies(0);
}

void Sheep::acceptVisit(Visitor& v)
{
    v.visit(this);
}

const Sheep* Sheep::getLeader() const
{
    return hasLeader() ? getAppEnv().getLeader(herdId) : nullptr;
}

int Sheep::getHerdId() const
{
    return herdId;
}

bool Sheep::hasLeader() const
{
    return herdId != -1;
}

bool Sheep::isLeader() const
{
    return getLeader() == this;
}

bool Sheep::isFreeToMove() const
{
    return isLeader() || !hasLeader();
}

std::string Sheep::getDebugString() const
{
    std::string herdString;
    if (hasLeader()) {
        herdString = (isLeader() ? "Leader" : "Follower") ;
        herdString += ", Herd: " + std::to_string(getHerdId());
    } else {
        herdString = "Not in herd";
    }
    return Animal::getDebugString() + herdString + "\n";
}

bool Sheep::canInfect(LivingEntity const * other) const
{
    return other->infectableBy(this);
}

bool Sheep::infectableBy(Sheep const * sheep) const
{
    return sheep != this &&
           sheep->hasVirus() &&
           sheep->getVirusQuantity() > getAppConfig().virus_min_quantity_for_infection &&
           bernoulli(getAppConfig().virus_infection_probability);
}