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
         * @brief Destructor.
         */
        ~Grass();

        /*!
         * @brief Draws the Grass in the given window.
         *
         * @param targetWindow the window to draw on
         */
        void drawOn(sf::RenderTarget& targetWindow) const override;

        /*!
         * @brief Updates the Grass size over time.
         *
         * @param dt the time passed
         */
        void update(sf::Time dt) override;

        /*!
         * @brief Checks if a LivingEntity is eatable by the current one using
         * the eatableBy methods
         *
         * @param other the LivingEntity to check
         *
         * @return True if other is eatable by this
         */
        bool eatable(LivingEntity const* other) const override;

        /*!
         * @brief Checks if this Grass is eatable by a Wolf
         *
         * @param wolf the Wolf
         *
         * @return False
         */
        bool eatableBy(Wolf  const* wolf) const override;

        /*!
         * @brief Checks if this Grass is eatable by a Sheep
         *
         * @param sheep the Sheep
         *
         * @return True
         */
        bool eatableBy(Sheep const* sheep) const override;

        /*!
         * @brief Checks if this Grass is eatable by a Grass
         *
         * @param grass the Grass
         *
         * @return False
         */
        bool eatableBy(Grass const* grass) const override;

        /*!
		 * @brief Returns the debug string of this Grass to be print on screen.
		 *
		 * @return the debug string (std::string)
		 */
		std::string getDebugString() const override;

        /*!
         * @brief Checks if the Grass is dead or not.
         *
         * @return True if the Grass ran out of energy or is too old
         */
        bool isDead() const override;

        /*!
         * @brief Gets the Grass radius, which is half its energy level.
         *
         * @return the Grass radius (double)
         */
        double getRadius() const override;
};

#endif // INFOSV_GRASS_HPP
