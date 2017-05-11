#include <Env/Environment.hpp>
#include <Env/Animal.hpp>
#include <Env/LivingEntity.hpp>
#include <algorithm>

Environment::~Environment() {

}

void Environment::addEntity(LivingEntity* entity)
{
    entities.push_back(entity);
}

void Environment::update(sf::Time dt)
{
    for(auto& entity: entities) {
        entity->update(dt);
        if(entity->isDead()) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.erase(std::remove(entities.begin(), entities.end(), nullptr), entities.end());
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
    for(auto& entity: entities) {
        entity->drawOn(targetWindow);
    }
}

void Environment::reset()
{
    for(auto& entity: entities) {
        delete entity;
    }
    entities.clear();
}

std::list<LivingEntity*> Environment::getEntitiesInSightForAnimal(const Animal* animal) const
{
    std::list<LivingEntity*> entitiesSeen;
    for(auto entity: entities) {
        if(entity != nullptr && animal->isTargetInSight(entity->getPosition())) {
            entitiesSeen.push_back(entity);
        }
    }
    return entitiesSeen;
}
