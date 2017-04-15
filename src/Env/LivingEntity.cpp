#include <Env/LivingEntity.hpp>
#include <Application.hpp>

LivingEntity::LivingEntity(const Vec2d& initPos, const double& startEnergy)
    : position(initPos), energy(startEnergy) {}

Vec2d LivingEntity::getPosition() const {
    return this->position;
}

void LivingEntity::setPosition(const Vec2d& newPosition) {
    Vec2d boundedPosition = newPosition;
    double maxWidth = getAppConfig().window_simulation_width;
    double maxHeight = getAppConfig().window_simulation_height;
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
    this->position = boundedPosition;
}

double LivingEntity::getEnergy() const {
    return this->energy;
}

void LivingEntity::setEnergy(const double& newEnergy) {
    this->energy = newEnergy;
}

const LivingEntity* LivingEntity::getClosestEntity(std::list<LivingEntity*> entities) const {
    LivingEntity* closest = entities.front();
    double currentDistance = distance(this->getPosition(), closest->getPosition());
    for(auto entity: entities) {
        double newDistance = distance(this->getPosition(), entity->getPosition());
        if(newDistance < currentDistance) {
            closest = entity;
            currentDistance = newDistance;
        }
    }
    return closest;
}
