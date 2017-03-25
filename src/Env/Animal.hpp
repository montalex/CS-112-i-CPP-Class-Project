#ifndef INFOSV_ANIMAL_HPP
#define INFOSV_ANIMAL_HPP

#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Arc.hpp>
#include <Config.hpp>

/*!
 * @class Animal
 *
 * @brief Represent an Animal in the simulation.
 *
 * Vec2d position: the Animal's position
 * Vec2d direction: the Animal's direction
 * Vec2d target: the Animal's target position
 * double speedNorm: the norm of the Animal's speed
 */
class Animal {
    public:
        /*!
         * @brief Constructor.
         *
         * @param initPos the Animla's initial position
         */
        Animal(const Vec2d& initPos);

        /*!
         * @brief Gets the Animal's maximum speed.
         *
         * @return the Animal's maximum speed (double)
         */
        double getStandardMaxSpeed() const;

        /*!
         * @brief Gets the Animal's mass.
         *
         * @return the Animal's mass (double)
         */
        double getMass() const;

        /*!
         * @brief Gets the Animal's radius.
         *
         * @return the Animal's radius (double)
         */
        double getRadius() const;

        /*!
         * @brief Sets the Animal's target position.
         *
         * @param target the new target position
         */
        void setTargetPosition(const Vec2d& target);

        /*!
         * @brief Gets the Animal's speed vector.
         *
         * @return the Animal's speed vector (Vec2d)
         */
        Vec2d getSpeedVector() const;

        /*!
         * @brief Gets the Animal's view range.
         *
         * @return the Animal's view range (double)
         */
        double getViewRange() const;

        /*!
         * @brief Gets the Animal's view distance.
         *
         * @return the Animal's view distance (double)
         */
        double getViewDistance() const;

        /*!
         * @brief Gets the Animal's view rotation.
         *
         * @return the Animal's view rotation (double)
         */
        double getRotation() const;

        /*!
         * @brief Sets the Animal's view rotation.
         *
         * @param angle the view rotation angle
         */
        void setRotation(const double& angle);

        /*!
         * @brief Updates the Animal's attributes over time.
         *
         * @param dt the time passed
         */
        void update(sf::Time dt);

        /*!
         * @brief Draws the Animal and his target in the given window.
         *
         * @param targetWindow the window to draw on
         */
        void drawOn(sf::RenderTarget& targetWindow) const;

        /*!
         * @brief Draws the Animal's vision in the given window.
         *
         * @param targetWindow the window to draw on
         */
        void drawVision(sf::RenderTarget& targetWindow) const;

        /*!
         * @brief Gets the Animal's attraction force to his target.
         *
         * @return Animal's attraction force to his target (Vec2d)
         */
        Vec2d attractionForce() const;

        /*!
         * @brief Gets the Deceleration constant for the Animal
         *        depending on the distance to his target.
         *
         * @param distanceToTarget the distance to the target
         *
         * @return the Deceleration coefficient (Deceleration enum)
         */
        Deceleration getDeceleration(const double& distanceToTarget) const;

    private:
        Vec2d position;
        Vec2d direction;
        Vec2d target;
        double speedNorm;
        double viewAngle;
        double viewMaxDistance;
};

#endif // INFOSV_ANIMAL_HPP
