#ifndef INFOSV_WOLF_HPP
#define INFOSV_WOLF_HPP

#include <Env/Animal.hpp>

/*!
 * @class Wolf
 *
 * @brief Represent a Wolf in the simulation.
 */
class Wolf : public Animal {
    /*!
     * @brief Gets the Wolf's maximum speed.
     *
     * @return the Wolf's maximum speed (double)
     */
    virtual double getStandardMaxSpeed() const override;

    /*!
     * @brief Gets the Wolf's mass.
     *
     * @return the Wolf's mass (double)
     */
    virtual double getMass() const override;

    /*!
     * @brief Gets the Wolf's radius.
     *
     * @return the Wolf's radius (double)
     */
    virtual double getRadius() const override;

    /*!
     * @brief Gets the Wolf's view range in radians.
     *
     * @return the Wolf's view range (double)
     */
    virtual double getViewRange() const override;

    /*!
     * @brief Gets the Wolf's view distance.
     *
     * @return the Wolf's view distance (double)
     */
    virtual double getViewDistance() const override;

    /*!
     * @brief Gets the Wolf's virtual target radius
     *
     * @return the Wolf's virtual target radius (double)
     */
    virtual double getRandomWalkRadius() const override;

    /*!
     * @brief Gets the Wolf's distance to his virtual target circle center
     *
     * @return the Wolf's distance to his virtual target circle center
     *         (double)
     */
    virtual double getRandomWalkDistance() const override;

    /*!
     * @brief Gets the Wolf's virtual target jitter
     *
     * @return the Wolf's virtual target jitter (double)
     */
    virtual double getRandomWalkJitter() const override;
};

#endif // INFOSV_WOLF_HPP
