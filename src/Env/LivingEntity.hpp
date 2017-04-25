#ifndef INFOSV_LIVING_ENTITY_HPP
#define INFOSV_LIVING_ENTITY_HPP

#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>

class Sheep;
class Wolf;
class Grass;

/*!
 * @class LivingEntity
 *
 * @brief Represent any LivingEntity in the simulation.
 *
 * Vec2d position: the LivingEntity's position
 * double energy: the LivingEntity's energy
 * sf::Time age: the LivingEntity's age
 */
class LivingEntity {
    public:
        /*!
         * @brief Constructor.
         *
         * @param initPos the LivingEntity's initial position
         * @param startEnergy the LivingEntity's starting energy level
         */
        LivingEntity(const Vec2d& initPos, const double& startEnergy);

        /*!
         * @brief Destructor.
         */
        virtual ~LivingEntity();

        /*!
         * @brief Gets the LivingEntity's position.
         *
         * @return the LivingEntity's position (Vec2d)
         */
        Vec2d getPosition() const;

        /*!
         * @brief Sets the LivingEntity's position to the given one. If the position
         *             is outside the the window, set it at the other end.
         *
         * @param newPosition the new position of the LivingEntity
         */
        void setPosition(const Vec2d& newPosition);

        /*!
         * @brief Gets the LivingEntity's energy.
         *
         * @return the LivingEntity's energy (double)
         */
        double getEnergy() const;

        /*!
         * @brief Sets the LivingEntity's energy to the given one.
         *
         * @param newEnergy the new energy of the LivingEntity
         */
        void setEnergy(const double& newEnergy);

        /*!
         * @brief Gets the LivingEntity's age.
         *
         * @return the LivingEntity's age (sf::Time)
         */
        sf::Time getAge() const;

        /*!
         * @brief Sets the LivingEntity's age to the given one.
         *
         * @param newAge the new age of the LivingEntity
         */
        void setAge(const sf::Time& newAge);

        /*!
         * @brief Draws the Entity in the given window.
         *
         * @param targetWindow the window to draw on
         */
        virtual void drawOn(sf::RenderTarget& targetWindow) const = 0;

        /*!
         * @brief Updates the Entity's position over time.
         *
         * @param dt the time passed
         */
        virtual void update(sf::Time dt);

        /*!
         * @brief Checks if a LivingEntity is eatable by the current one using
         * the eatableBy methods
         *
         * @param other the LivingEntity to check
         *
         * @return True if the  LivingEntity is eatable
         */
        virtual bool eatable(LivingEntity const* other) const = 0;

        /*!
         * @brief Checks if this Entity is eatable by a Wolf
         *
         * @param wolf the Wolf
         *
         * @return True if this Entity is eatable by a Wolf
         */
        virtual bool eatableBy(Wolf  const* wolf) const = 0;

        /*!
         * @brief Checks if this Entity is eatable by a Sheep
         *
         * @param sheep the Sheep
         *
         * @return True if this Entity is eatable by a Sheep
         */
        virtual bool eatableBy(Sheep const* sheep) const = 0;

        /*!
         * @brief Checks if this Entity is eatable by a Grass
         *
         * @param grass the Grass
         *
         * @return True if this Entity is eatable by a Grass
         */
        virtual bool eatableBy(Grass const* grass) const = 0;

        /*!
         * @brief Gets the closest entity to the current one from a given list.
         *
         * @param  entities the list entities
         *
         * @return the LivingEntity closest to current one
         */
        const LivingEntity* getClosestEntity(std::list<LivingEntity*> entities) const;

        /*!
         * @brief Returns the debug string of this LivingEntity to be print on screen.
         *
         * @return the debug string (std::string)
         */
        virtual std::string getDebugString() const = 0;

        /*!
         * @brief Checks if the LivingEntity is dead or not.
         *
         * @return True if the LivingEntity ran out of energy or is too old
         */
        virtual bool isDead() const;

    private:
        Vec2d position;
        double energy;
        sf::Time age;
};

#endif // INFOSV_LIVING_ENTITY_HPP
