#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>

/* Represent the Animal's automaton which follows a target
 *
 * Vec2d position: the SeekingAutomaton's position
 * Vec2d direction: the SeekingAutomaton's direction
 * Vec2d target: the SeekingAutomaton's target
 * double speedNorm: the norm of the SeekingAutomaton's speed
 */
class SeekingAutomaton {
        private:
                Vec2d position;
                Vec2d direction;
                Vec2d target;
                double speedNorm;
        public:
                //Constructor
                SeekingAutomaton(const Vec2d& initPos);
                //Return the SeekingAutomaton's maximum speed
                double getStandardMaxSpeed() const;
                //Returns the SeekingAutomaton's mass
                double getMass() const;
                //Returns the SeekingAutomaton's radius
                double getRadius() const;
                //Set the SeekingAutomaton's target
                void setTargetPosition(const Vec2d& target);
                //Returns the SeekingAutomaton's speed vector
                Vec2d getSpeedVector() const;
                //Updates the SeekingAutomaton's positing in time
                void update(sf::Time dt);
                //Draws the SeekingAutomaton in the given window
                void drawOn(sf::RenderTarget& targetWindow) const;
                //Returns the SeekingAutomaton's attraction force to the target
                Vec2d attractionForce() const;
                //Returns the Deceleration constant for the SeekingAutomaton
                //depending on the distance to his target
                Deceleration getDeceleration(const double& distanceToTarget) const;
};
