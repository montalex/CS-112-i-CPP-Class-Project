#ifndef INFOSV_WOLF_HPP
#define INFOSV_WOLF_HPP

#include <Env/Animal.hpp>

/*!
 * @class Wolf
 *
 * @brief Represent a Wolf in the simulation.
 */
class Wolf : public Animal {
    public:
        /*!
         * @brief Constructor.
         *
         * @param initPos the Wolf's initial position
         * @param mother Mother's genome of the Wolf
         * @param father Father's genome of the Wolf
         */
        Wolf(const Vec2d& initPos, Genome *mother = nullptr, Genome *father = nullptr);

        /*!
         * @brief Destructor.
         */
        ~Wolf();

        /*!
         * @brief Gets the Wolf's maximum speed.
         *
         * @return the Wolf's maximum speed (double)
         */
        double getStandardMaxSpeed() const override;

        /*!
         * @brief Gets the Wolf's mass.
         *
         * @return the Wolf's mass (double)
         */
        double getMass() const override;

        /*!
         * @brief Gets the Wolf's radius.
         *
         * @return the Wolf's radius (double)
         */
        double getRadius() const override;

        /*!
         * @brief Get's the Wolf's texture.
         *
         * @return the Wolf's texture.
         */
        sf::Texture& getTexture() const override;

        /*!
         * @brief Gets the Wolf's view range in radians.
         *
         * @return the Wolf's view range (double)
         */
        double getViewRange() const override;

        /*!
         * @brief Gets the Wolf's view distance.
         *
         * @return the Wolf's view distance (double)
         */
        double getViewDistance() const override;

        /*!
         * @brief Gets the Wolf's virtual target radius
         *
         * @return the Wolf's virtual target radius (double)
         */
        double getRandomWalkRadius() const override;

        /*!
         * @brief Gets the Wolf's distance to his virtual target circle center
         *
         * @return the Wolf's distance to his virtual target circle center
         *         (double)
         */
        double getRandomWalkDistance() const override;

        /*!
         * @brief Gets the Wolf's virtual target jitter
         *
         * @return the Wolf's virtual target jitter (double)
         */
        double getRandomWalkJitter() const override;

};

#endif // INFOSV_WOLF_HPP
