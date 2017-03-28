#ifndef INFOSV_ANIMAL_HPP
#define INFOSV_ANIMAL_HPP

#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Arc.hpp>
#include <Config.hpp>
#include <Application.hpp>
#include <Random/Random.hpp>

/*!
 * @class Animal
 *
 * @brief Represent an Animal in the simulation.
 *
 * Vec2d position: the Animal's position
 * Vec2d direction: the Animal's direction in the Animal's coordinate system.
 * Vec2d target: the Animal's target position
 * Vec2d virtual_target: the Animal's virtual target position in the Animal's
 *                       coordinate system.
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
         * @brief Gets the Animal's position.
         *
         * @return the Animal's position (Vec2d)
         */
        Vec2d getPosition() const;

        /*!
         * @brief Sets the Animal's position to the given one. If the position
         *             is outside the the window, set it at the other end.
         *
         * @param newPosition the new position of the Animal
         */
        void setPosition(const Vec2d& newPosition);

        /*!
         * @brief Gets the Animal's direction.
         *
         * @return the Animal's direction (Vec2d)
         */
        Vec2d getDirection() const;

        /*!
         * @brief Sets the Animal's direction.
         *
         * @param newDirection the new direction of the Animal
         */
        void setDirection(const Vec2d& newDirection);

        /*!
         * @brief Gets the Animal's target position.
         *
         * @return the Animal's target position (Vec2d)
         */
        Vec2d getTarget() const;

        /*!
         * @brief Sets the Animal's target position.
         *
         * @param target the new target position
         */
        void setTarget(const Vec2d& target);

        /*!
         * @brief Gets the Animal's virtual target position.
         *
         * @return the Animal's virtual target position (Vec2d)
         */
        Vec2d getVirtualTarget() const;

        /*!
         * @brief Sets the Animal's virtual target position.
         *
         * @param target the new virtual target position
         */
        void setVirtualTarget(const Vec2d& target);

        /*!
         * @brief Gets the Animal's speed norm.
         *
         * @return the Animal's speed norm (double)
         */
        double getSpeedNorm() const;

        /*!
         * @brief Sets the Animal's speed norm.
         *
         * @param newNorm the new speed norm.
         */
        void setSpeedNorm(const double& newNorm);

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
         * @brief Gets the Animal's speed vector.
         *
         * @return the Animal's speed vector (Vec2d)
         */
        Vec2d getSpeedVector() const;

        /*!
         * @brief Gets the Animal's view range in radians.
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
         * @brief Gets the Animal's virtual target radius
         *
         * @return the Animal's virtual target radius (double)
         */
        double getRandomWalkRadius() const;

        /*!
         * @brief Gets the Animal's distance to his virtual target circle center
         *
         * @return the Animal's distance to his virtual target circle center
         *         (double)
         */
        double getRandomWalkDistance() const;

        /*!
         * @brief Gets the Animal's virtual target jitter
         *
         * @return the Animal's virtual target jitter (double)
         */
        double getRandomWalkJitter() const;

        /*!
         * @brief Updates the Animal's target and calls updatePosition to modify
         *        its attribute over time.
         *
         * @param dt the time passed
         */
        void update(sf::Time dt);

        /*!
         * @brief Update the Animal's position, direction & speed norm over time
         *        according to its attraction force.
         *
         * @param dt the time passed
         * @param attractionForce the attraction force
         */
        void updatePosition(sf::Time dt, const Vec2d& attractionForce);

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
         * @brief Draws the Animal's virtual target in the given window.
         *
         * @param targetWindow the window to draw on
         */
        void drawVirtualTarget(sf::RenderTarget& targetWindow) const;

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

        /*!
         * @brief Tests if target is in sight.
         *
         * @param target the target position
         *
         * @return True if target is in sight
         */
        bool isTargetInSight(const Vec2d& target) const;

        /*!
         * @brief Compute the Animal's random movement according to its virtual
         *        target and returns its attraction force.
         *
         * @return Vec2 the new attraction force
         */
        Vec2d randomWalk();

        /*!
         * @brief Converts a vector in Animal's coordinates in global coordinates.
         *
         * @param coordinates the vector to Converts
         *
         * @return the vector in global coordinates (Vec2d)
         */
        Vec2d convertToGlobalCoord(const Vec2d& coordinates) const ;

    private:
        Vec2d position;
        Vec2d direction;
        Vec2d target;
        Vec2d virtual_target;
        double speedNorm;
};

#endif // INFOSV_ANIMAL_HPP
