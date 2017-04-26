#ifndef INFOSV_OBSTACLE_HPP
#define INFOSV_OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <Utility/Arc.hpp>
#include <Utility/Vec2d.hpp>

/*!
 * @class Obstacle
 *
 * @brief Represent Obstacles in the simulation with a cercle surounding it.
 *
 * Vec2d center: The Obstacle's center
 * double rad: The Obstacle's radius
 */
class Obstacle
{
public:
    /*!
     * @brief Gets the Obstacle's center.
     *
     * @return the Obstacle's center (Vec2d)
     */
    virtual Vec2d getCenter() const = 0;

    /*!
     * @brief Gets the Obstacle's radius.
     *
     * @return the Obstacle's radius (Vec2d)
     */
    virtual double getRadius() const  = 0;

    /*!
     * @brief Draws the Obstacle circle for debug mode.
     *
     * @param targetWindow the window to draw on
     */
    void drawObstacle(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Tests if the Obstacle is colliding with an other
     *
     * @param other the other Obstacle
     *
     * @return True if the current Obstacle is colliding with the other
     */
    bool isColliding(const Obstacle& other) const;

    /*!
     * @brief Tests a p is inside the current Obstacle
     *
     * @param p the point
     *
     * @return True if the point p is inside the current Obstacle
     */
    bool isPointInside(const Vec2d& p) const;

    /*!
     * @brief Operator for collisions.
     *
     * @param other the other Obstacle
     */
    bool operator|(Obstacle& other) const;

    /*!
     * @brief Operator to check if a point is inside the Obstacle.
     *
     * @param p the point
     */
    bool operator>(Vec2d& p) const;
};
#endif // INFOSV_OBSTACLE_HPP
