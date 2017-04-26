#ifndef INFOSV_WOLF_HPP
#define INFOSV_WOLF_HPP

#include <Env/Animal.hpp>

/*!
 * @class Wolf
 *
 * @brief Represent a Wolf in the simulation.
 */
class Wolf : public Animal
{
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
     * @brief Checks if this Wolf is eatable by a Wolf
     *
     * @param wolf the Wolf
     *
     * @return False
     */
    bool eatableBy(Wolf  const* wolf) const override;

    /*!
     * @brief Checks if this Wolf is eatable by a Sheep
     *
     * @param sheep the Sheep
     *
     * @return False
     */
    bool eatableBy(Sheep const* sheep) const override;

    /*!
     * @brief Checks if this Wolf is eatable by a Grass
     *
     * @param grass the Grass
     *
     * @return False
     */
    bool eatableBy(Grass const* grass) const override;

    /*!
     * @brief Checks if the Wolf is dead or not.
     *
     * @return True if the Wolf ran out of energy or is too old
     */
    bool isDead() const override;

    /*!
     * @brief Updates the Wolf's target and modify its attribute over time.
     *
     * @param dt the time passed
     */
    void update(sf::Time dt) override;

    /*!
     * @brief Feeds the Wolf with the given entity, to regain energy and
     * decrease the entity's energy.
     *
     * @param entity the LivingEntity to be eaten
     *
     * @return the energy left in the entity after the Wolf ate it.
     */
    double feed(LivingEntity *entity) override;
};

#endif // INFOSV_WOLF_HPP
