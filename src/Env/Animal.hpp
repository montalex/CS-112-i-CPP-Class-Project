#ifndef INFOSV_ANIMAL_HPP
#define INFOSV_ANIMAL_HPP

#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Arc.hpp>
#include <Config.hpp>

/* Represent an Animal in the simulation
 *
 * Vec2d position: the Animal's position
 * Vec2d direction: the Animal's direction
 * Vec2d target: the Animal's target
 * double speedNorm: the norm of the Animal's speed
 */
class Animal {
        private:
                Vec2d position;
                Vec2d direction;
                Vec2d target;
                double speedNorm;
                double viewAngle;
                double viewMaxDistance;
        public:
                //Constructor
                Animal(const Vec2d& initPos);
                //Return the Animal's maximum speed
                double getStandardMaxSpeed() const;
                //Returns the Animal's mass
                double getMass() const;
                //Returns the Animal's radius
                double getRadius() const;
                //Set the Animal's target
                void setTargetPosition(const Vec2d& target);
                //Returns the Animal's speed vector
                Vec2d getSpeedVector() const;
                //Returns the Animal's view angle
                double getViewRange() const;
                //Returns the Animal's view distance
                double getViewDistance() const;
                //Returns the direction vector's angle
                double getRotation() const;
                //Updates the Animal's direction vector with given angle
                void setRotation(const double& angle);
                //Updates the Animal's positing in time
                void update(sf::Time dt);
                //Draws the Animal in the given window
                void drawOn(sf::RenderTarget& targetWindow) const;
                //Draws the Animal's vision in the given window
                void drawVision(sf::RenderTarget& targetWindow) const;
                //Returns the Animal's attraction force to the target
                Vec2d attractionForce() const;
                //Returns the Deceleration constant for the Animal
                //depending on the distance to his target
                Deceleration getDeceleration(const double& distanceToTarget) const;
};

#endif // INFOSV_ANIMAL_HPP