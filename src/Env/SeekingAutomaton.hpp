#ifndef INFOSV_SEEKING_AUTOMATON_HPP
#define INFOSV_SEEKING_AUTOMATON_HPP

#include <Utility/Vec2d.hpp>
#include <Utility/Constants.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>

/*!
 * @class SeekingAutomaton
 *
 * @brief Represent the Animal's automaton which follows a target
 *
 * Vec2d position: the SeekingAutomaton's position
 * Vec2d direction: the SeekingAutomaton's direction
 * Vec2d target: the SeekingAutomaton's target
 * double speedNorm: the norm of the SeekingAutomaton's speed
 */
class SeekingAutomaton
{
public:
    /*!
     * @brief Constructor.
     *
     * @param initPos the SeekingAutomaton's initial position
     */
    SeekingAutomaton(const Vec2d& initPos);

    /*!
     * @brief Gets the SeekingAutomaton's maximum speed.
     *
     * @return the SeekingAutomaton's maximum speed (double)
     */
    double getStandardMaxSpeed() const;

    /*!
     * @brief Gets the SeekingAutomaton's mass.
     *
     * @return the SeekingAutomaton's mass (double)
     */
    double getMass() const;

    /*!
     * @brief Gets the SeekingAutomaton's radius.
     *
     * @return the SeekingAutomaton's radius (double)
     */
    double getRadius() const;

    /*!
     * @brief Sets the SeekingAutomaton's target position.
     *
     * @param target the new target position
     */
    void setTargetPosition(const Vec2d& target);

    /*!
     * @brief Gets the SeekingAutomaton's speed vector.
     *
     * @return the SeekingAutomaton's speed vector (Vec2d)
     */
    Vec2d getSpeedVector() const;

    /*!
     * @brief Updates the SeekingAutomaton's attributes over time.
     *
     * @param dt the time passed
     */
    void update(sf::Time dt);

    /*!
     * @brief Draws the SeekingAutomaton and his target in the given window.
     *
     * @param targetWindow the window to draw on
     */
    void drawOn(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Gets the SeekingAutomaton's attraction force to his target.
     *
     * @return SeekingAutomaton's attraction force to his target (Vec2d)
     */
    Vec2d attractionForce() const;

    /*!
     * @brief Gets the Deceleration constant for the SeekingAutomaton
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
};
#endif // INFOSV_SEEKING_AUTOMATON_HPP
