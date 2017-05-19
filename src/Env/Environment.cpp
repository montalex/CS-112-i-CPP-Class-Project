#include <Env/Environment.hpp>
#include <Env/Animal.hpp>
#include <Env/LivingEntity.hpp>
#include <Utility/Constants.hpp>
#include <algorithm>
#include <Env/SpeciesCounter.hpp>
#include <Env/OldestSheepFinder.hpp>
#include <Application.hpp>

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
    }
    updateHerds();

    for(auto& entity: entities) {
        if(entity->isDead()) {
            if (tracked == entity) {
                tracked = nullptr;
            }
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
    std::unordered_map<std::string, double> empty;

    if (label == s::GENERAL) {
        SpeciesCounter sc;
        for (LivingEntity * const entity : entities) {
            entity->acceptVisit(sc);
        }
        return sc.getCount();
    }

    if (label == s::GRASS_INDIVIDUAL || label == s::ANIMAL_INDIVIDUAL) {
        std::unordered_map<std::string, double> init = {
            {s::ENERGY, 0},
            {s::HEALTH, 0}, 
            {s::HEALTH, 0},
            {s::VIRUS, 0},
            {s::ADASCORE, 0},
            {s::IMUNAC, 0},
            {s::SCORE, 0}
        };
        //return tracked == nullptr ? empty : tracked->getStats();
        return tracked == nullptr ? init : tracked->getStats();

    }

    return empty;
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
    // Use OldestSheepFinder visitor to retrieve new leader.
    OldestSheepFinder finder(herd);
    for (LivingEntity* const entity : entities) {
        entity->acceptVisit(finder);
    }

    return finder.getOldestVisited();
}

void Environment::updateHerds() {
    std::list<int> toErase; //Store dead leaders for later remove them from map

    for (std::pair<const int, const Sheep*> & entry : sheepLeaders) {
        if (entry.second->isDead()) {
            const Sheep* oldestSheep = findOldestSheep(entry.first);
            if (oldestSheep == nullptr) { 
                // No oldest means all the herd is dead.
                toErase.push_back(entry.first);
            } else {
                sheepLeaders[entry.second->getHerdId()] = findOldestSheep(entry.first);
            }
        }
    }
    for (int &t : toErase) {
        sheepLeaders.erase(t);
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

const LivingEntity* Environment::getTrackedEntity() const {
    return tracked;
}

void Environment::trackEntity(Vec2d position) {
    LivingEntity* closest = nullptr;
    double distanceFromClosest = std::numeric_limits<double>::max();
    // Track element closest to given position
    for (LivingEntity* entity : entities) {
        double distance = (position - entity->getPosition()).length();
        if (distance < distanceFromClosest) {
            closest = entity;
            distanceFromClosest = distance;
        }
    }

    tracked = closest;
    getApp().focusOnStat(tracked->getStatLabel());
}

void Environment::stopTrackingAnyEntity() {
    tracked = nullptr;
    getApp().focusOnStat(s::GENERAL);
}
