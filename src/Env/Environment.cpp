#include <Env/Environment.hpp>
#include <Env/Animal.hpp>
#include <Env/LivingEntity.hpp>
#include <Utility/Constants.hpp>
#include <algorithm>
#include <Env/SpeciesCounter.hpp>
#include <Env/OldestSheepFinder.hpp>

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
        updateHerds();
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

std::unordered_map<std::string, double> Environment::fetchData(std::string const & label) {
    if (label == s::GENERAL) {
        SpeciesCounter sc;
        for (LivingEntity * const entity : entities) {
            entity->acceptVisit(sc);
        }
        return sc.getCount();
    } else {
        std::unordered_map<std::string, double> empty;
        return empty;
    }

}

const Sheep* Environment::getLeader(int herdId) const  {
    return sheepLeaders.at(herdId);
}

void Environment::addToHerd(const Sheep * const sheep) {
    int herdId = sheep->getHerdId();
    // The simplest and most efficient way to check whether a map contains a certain key
    // is to count its occurrences.
    if (sheepLeaders.count(herdId) == 0) {
        sheepLeaders[herdId] = sheep;
    }
}

const Sheep* Environment::findOldestSheep(int herd) {
    OldestSheepFinder finder(herd);
    for (LivingEntity* const entity : entities) {
        entity->acceptVisit(finder);
    }
    return finder.getOldestVisited();
}

void Environment::updateHerds() {
    for (std::pair<const int, const Sheep*> entry : sheepLeaders) {
        if (entry.second->isDead()) {
            const Sheep* oldestSheep = findOldestSheep(entry.first);
            if (oldestSheep == nullptr) {
                std::cout << "NO MORE BREBIS IN HERD " << entry.first << std::endl;
                sheepLeaders.erase(entry.first);
            } else {
                sheepLeaders[entry.second->getHerdId()] = findOldestSheep(entry.first);
            }
        }
    }
}

std::list<LivingEntity*> Environment::getNearbyAvoidableEntitesForAnimal(const Animal* animal) const
{
    std::list<LivingEntity*> entitiesToAvoid;
    for(auto entity: entities) {
        double distance = (entity->getPosition() - animal->getPosition()).length();
        if(entity != nullptr && entity != animal && !animal->eatable(entity) && distance <= ANIMAL_PROXIMITY_MIN) {
            entitiesToAvoid.push_back(entity);
        }
    }
    return entitiesToAvoid;
}
