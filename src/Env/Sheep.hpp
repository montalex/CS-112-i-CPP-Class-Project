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
};

#endif // INFOSV_SHEEP_HPP
