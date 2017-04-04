#include <Env/Environment.hpp>
#include <Env/Animal.hpp>
#include <Env/LivingEntity.hpp>

void Environment::addEntity(LivingEntity* entity) {
    entities.push_back(entity);
}

void Environment::update(sf::Time dt) {
    for(auto& entity: entities) {
        entity->update(dt);
    }
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const {
    for(auto& entity: entities) {
        entity->drawOn(targetWindow);
    }
}

void Environment::reset() {
    entities.clear();
}

std::list<LivingEntity*> Environment::getEntitiesInSightForAnimal(const Animal* animal) const {
    std::list<LivingEntity*> entitiesSeen;
    for(auto entity: entities) {
        if(animal->isTargetInSight(entity->getPosition())) {entitiesSeen.push_back(entity);}
    }
    return entitiesSeen;
}
