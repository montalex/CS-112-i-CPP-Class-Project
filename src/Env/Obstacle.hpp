#ifndef INFOSV_OBSTACLE_HPP
#define INFOSV_OBSTACLE_HPP

#include <Utility/Vec2d.hpp>

/*!
 * @class Obstacle
 *
 * @brief Represent Obstacles in the simulation with a cercle surounding it.
 *
 * Vec2d center: The Obstacle's center
 * double rad: The Obstacle's radius
 */
class Obstacle {
    public:
        /*!
         * @brief Constructor.
         *
         * @param center the Obstacle's center position
         * @param rad the Obstacle's radius
         */
        Obstacle(Vec2d center, double rad);

        /*!
         * @brief Remove default constructor
         */
        Obstacle() = delete;

        /*!
         * @brief Gets the Obstacle's center.
         *
         * @return the Obstacle's center (Vec2d)
         */
        Vec2d getCenter();

        /*!
         * @brief Gets the Obstacle's radius.
         *
         * @return the Obstacle's radius (Vec2d)
         */
        double getRadius();

        /*!
         * @brief Tests if the Obstacle is colliding with an other
         *
         * @param other the other Obstacle
         *
         * @return True if the current Obstacle is colliding with the other
         */
        bool isColliding(const Obstacle& other);

        /*!
         * @brief Tests a p is inside the current Obstacle
         *
         * @param p the point
         *
         * @return True if the point p is inside the current Obstacle
         */
        bool isPointInside(const Vec2d& p);

        /*!
         * @brief Operator for collisions.
         *
         * @param other the other Obstacle
         */
        bool operator|(Obstacle& other);

        /*!
         * @brief Operator to check if a point is inside the Obstacle.
         *
         * @param p the point
         */
        bool operator>(Vec2d& p);

    private:
        Vec2d center;
        double rad;

};
#endif // INFOSV_OBSTACLE_HPP
