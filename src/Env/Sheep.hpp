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
         * @brief Gets the Sheep's maximum speed.
         *
         * @return the Sheep's maximum speed (double)
         */
        virtual double getStandardMaxSpeed() const override;

        /*!
         * @brief Gets the Sheep's mass.
         *
         * @return the Sheep's mass (double)
         */
        virtual double getMass() const override;

        /*!
         * @brief Gets the Sheep's radius.
         *
         * @return the Sheep's radius (double)
         */
        virtual double getRadius() const override;

        /*!
         * @brief Gets the Sheep's view range in radians.
         *
         * @return the Sheep's view range (double)
         */
        virtual double getViewRange() const override;

        /*!
         * @brief Gets the Sheep's view distance.
         *
         * @return the Sheep's view distance (double)
         */
        virtual double getViewDistance() const override;

        /*!
         * @brief Gets the Sheep's virtual target radius
         *
         * @return the Sheep's virtual target radius (double)
         */
        virtual double getRandomWalkRadius() const override;

        /*!
         * @brief Gets the Sheep's distance to his virtual target circle center
         *
         * @return the Sheep's distance to his virtual target circle center
         *         (double)
         */
        virtual double getRandomWalkDistance() const override;

        /*!
         * @brief Gets the Sheep's virtual target jitter
         *
         * @return the Sheep's virtual target jitter (double)
         */
        virtual double getRandomWalkJitter() const override;
};

#endif // INFOSV_SHEEP_HPP
