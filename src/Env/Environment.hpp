#ifndef INFOSV_ENVIRONMENT_HPP
#define INFOSV_ENVIRONMENT_HPP

#include <list>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>

class Animal;
class LivingEntity;

/*!
 * @class Environment
 *
 * @brief Represents the simulation's Environment.
 *
 * list<LivingEntity> entities: the entity population in the Environment
 */
class Environment {

    public:
        //Using default constructor for now

        /*!
         * @brief Adds an entity to the Environment.
         *
         * @param entity the new LivingEntity
         */
        void addEntity(LivingEntity* entity);

        /*!
         * @brief Removes an entity to the Environment and destroys it.
         *
         * @param entity the LivingEntity to remove
         */
        void removeEntity(LivingEntity* entity);

        /*!
         * @brief Updates the Environment through time.
         *
         * @param dt the time passed
         */
        void update(sf::Time dt);

        /*!
         * @brief Draws the Environment in the given window.
         *
         * @param targetWindow the window to draw on
         */
        void drawOn(sf::RenderTarget& targetWindow) const;

        /*!
         * @brief Resets and empties the Environment.
         */
        void reset();

        /*!
         * @brief Gets all entities that the given Animal see in the Environment.
         *
         * @param animal the Animal
         *
         * @return all entities that the Animal sees
         */
        std::list<LivingEntity*> getEntitiesInSightForAnimal(const Animal* animal) const;

    private:
        std::list<LivingEntity*> entities;
};
#endif // INFOSV_ENVIRONMENT_HPP
