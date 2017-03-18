#include <Utility/Vec2d.hpp>

/* Represent all obstacle in the simulation with a cercle surounding it.
 *
 * Vec2d center: The Obstacle's center
 * double rad: The Obstacle's radius
 */
class Obstacle {
        private:
                Vec2d center;
                double rad;

        public:
                //Constructor
                Obstacle(Vec2d pos, double rad);
                //Remove default constructor
                Obstacle() = delete;
                //Returns the Obstacle's center
                Vec2d getCenter();
                //Returns the Obtacle's raduis
                double getRadius();
                //Returns True if the current Obstacle is colliding with the other
                bool isColliding(const Obstacle& other);
                //Returns True if the point p is inside the current Obstacle
                bool isPointInside(const Vec2d& p);
                //Operator for collisions
                bool operator|(Obstacle& other);
                //Operator to check if point p is inside
                bool operator>(Vec2d& p);
};
