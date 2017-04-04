#ifndef INFOSV_GRASS_HPP
#define INFOSV_GRASS_HPP

#include <Env/LivingEntity.hpp>

/*!
 * @class Grass
 *
 * @brief Represent a Grass food ressource in the simulation. Its size is equivalent
 * to it's energy level.
 */
class Grass : public LivingEntity {
    public:
        /*!
         * @brief Constructor.
         *
         * @param initPos the Grass initial position
         */
        Grass(const Vec2d& initPos);

        /*!
         * @brief Draws the Grass in the given window.
         *
         * @param targetWindow the window to draw on
         */
        void drawOn(sf::RenderTarget& targetWindow) const override;

        /*!
         * @brief Updates the Grass size over time
         *
         * @param dt the time passed
         */
        void update(sf::Time dt) override;
};

#endif // INFOSV_GRASS_HPP
