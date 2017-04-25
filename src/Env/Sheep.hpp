#ifndef INFOSV_SHEEP_HPP
#define INFOSV_SHEEP_HPP

#include <Env/Animal.hpp>

/*!
 * @class Sheep
 *
 * @brief Represent a Sheep in the simulation.
 */
class Sheep : public Animal {
    public:
        /*!
         * @brief Constructor.
         *
         * @param initPos the Sheep's initial position
         * @param mother Mother's genome of the Sheep
         * @param father Father's genome of the Sheep
         */
        Sheep(const Vec2d& initPos, Genome *mother = nullptr, Genome *father = nullptr);

        /*!
         * @brief Destructor.
         */
        ~Sheep();

        /*!
         * @brief Gets the Sheep's maximum speed.
         *
         * @return the Sheep's maximum speed (double)
         */
        double getStandardMaxSpeed() const override;

        /*!
         * @brief Gets the Sheep's mass.
         *
         * @return the Sheep's mass (double)
         */
        double getMass() const override;

        /*!
         * @brief Gets the Sheep's radius.
         *
         * @return the Sheep's radius (double)
         */
        double getRadius() const override;

        /*!
         * @brief Get's the Sheep's texture.
         *
         * @return the Sheep's texture.
         */
        sf::Texture& getTexture() const override;

        /*!
         * @brief Gets the Sheep's view range in radians.
         *
         * @return the Sheep's view range (double)
         */
        double getViewRange() const override;

        /*!
         * @brief Gets the Sheep's view distance.
         *
         * @return the Sheep's view distance (double)
         */
        double getViewDistance() const override;

        /*!
         * @brief Gets the Sheep's virtual target radius
         *
         * @return the Sheep's virtual target radius (double)
         */
        double getRandomWalkRadius() const override;

        /*!
         * @brief Gets the Sheep's distance to his virtual target circle center
         *
         * @return the Sheep's distance to his virtual target circle center
         *         (double)
         */
        double getRandomWalkDistance() const override;

        /*!
         * @brief Gets the Sheep's virtual target jitter
         *
         * @return the Sheep's virtual target jitter (double)
         */
        double getRandomWalkJitter() const override;

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
         * @brief Checks if this Sheep is eatable by a Wolf
         *
         * @param wolf the Wolf
         *
         * @return True
         */
        bool eatableBy(Wolf  const* wolf) const override;

        /*!
         * @brief Checks if this Sheep is eatable by a Sheep
         *
         * @param sheep the Sheep
         *
         * @return False
         */
        bool eatableBy(Sheep const* sheep) const override;

        /*!
         * @brief Checks if this Sheep is eatable by a Grass
         *
         * @param grass the Grass
         *
         * @return False
         */
        bool eatableBy(Grass const* grass) const override;

        /*!
         * @brief Checks if the Sheep is dead or not.
         *
         * @return True if the Sheep ran out of energy or is too old
         */
        bool isDead() const override;

        /*!
         * @brief Updates the Sheep's target and modify its attribute over time.
         *
         * @param dt the time passed
         */
        void update(sf::Time dt) override;
};

#endif // INFOSV_SHEEP_HPP
