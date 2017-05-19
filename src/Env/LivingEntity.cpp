#include <Env/LivingEntity.hpp>
#include <Application.hpp>

LivingEntity::LivingEntity(const Vec2d& initPos, const double& startEnergy)
    : position(initPos), energy(startEnergy), age(sf::Time::Zero) {}

LivingEntity::~LivingEntity() {};

Vec2d LivingEntity::getPosition() const
{
    return position;
}

void LivingEntity::setPosition(const Vec2d& newPosition)
{
    Vec2d boundedPosition = newPosition;
    double maxWidth = getAppConfig().simulation_world_size;
    double maxHeight = getAppConfig().simulation_world_size;
    if(newPosition.x > maxWidth) {
        boundedPosition.x = 0;
    } else if(newPosition.x < 0) {
        boundedPosition.x = maxWidth;
    }
    if(newPosition.y > maxHeight) {
        boundedPosition.y = 0;
    } else if(newPosition.y < 0) {
        boundedPosition.y = maxHeight;
    }
    position = boundedPosition;
}

double LivingEntity::getEnergy() const
{
    return energy;
}

void LivingEntity::setEnergy(const double& newEnergy)
{
    energy = newEnergy;
}

sf::Time LivingEntity::getAge() const
{
    return age;
}

void LivingEntity::setAge(const sf::Time& newAge)
{
    age = newAge;
}

void LivingEntity::update(sf::Time dt)
{
    sf::Time newAge = getAge() + dt;
    setAge(newAge);
}

LivingEntity* LivingEntity::getClosestEntity(std::list<LivingEntity*> entities) const
{
    LivingEntity* closest = entities.front();
    double currentDistance = distance(getPosition(), closest->getPosition());
    for(auto entity: entities) {
        double newDistance = distance(getPosition(), entity->getPosition());
        if(newDistance < currentDistance) {
            closest = entity;
            currentDistance = newDistance;
        }
    }
    return closest;
}

bool LivingEntity::isDead() const
{
    return getAge() > sf::seconds(1E9) || getEnergy() <= 0.0;
}

Vec2d LivingEntity::getCenter() const
{
    return getPosition();
}

bool LivingEntity::isTracked() const {
    return this == getAppEnv().getTrackedEntity();
}

void LivingEntity::drawOn(sf::RenderTarget& targetWindow) const {
    if (isTracked()) {
        auto trackedSprite = buildSprite(getPosition() + Vec2d(-getRadius() / 3, getRadius() / 3),
                                         getRadius() / 2,
                                         getAppTexture(getAppConfig().entity_texture_tracked));
        targetWindow.draw(trackedSprite);
    }
}

std::unordered_map<std::string, double> LivingEntity::getStats() const {
    return {{s::ENERGY, energy}};
}
