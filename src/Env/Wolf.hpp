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

    /*!
     * @brief Checks if a LivingEntity is matable by the current Wolf using
     * the canMate methods
     *
     * @param other the LivingEntity to check
     *
     * @return True if the  LivingEntity is matable
     */
    bool matable(LivingEntity const* other) const override;

    /*!
     * @brief Checks if this Wolf can mate a Wolf
     *
     * @param wolf the Wolf
     *
     * @return True if the two Wolfs are of opposite sex.
     */
    bool canMate(Wolf const* wolf) const override;

    /*!
     * @brief Checks if this Wolf can mate a Sheep
     *
     * @param sheep the Sheep
     *
     * @return False
     */
    bool canMate(Sheep const* sheep) const override;

    /*!
     * @brief Checks if this Wolf can mate a Grass
     *
     * @param grass the Grass
     *
     * @return False
     */
    bool canMate(Grass const* grass) const override;

    /*!
     * @brief Breeds the Wolf with the given entity.
     *
     * @param entity the LivingEntity mate with
     */
    void meet(LivingEntity* mate) override;

    /*!
     * @brief Breeds the Wolf with the given wolf.
     *
     * @param wolf the Wolf to mate with.
     */
    void breed(Wolf* wolf) override;

    /*!
     * @brief Doesn't do anything as Wolfs can't mate with Sheep.
     *
     * @param sheep the Sheep to mate with.
     */
    void breed(Sheep* sheep) override;

    /*!
     * @brief Doesn't do anything as Wolf can't mate with Grass.
     *
     * @param grass the Grass to mate with
     */
    void breed(Grass* grass) override;

    /*!
     * @brief Give birth to children, adding new Wolfs to the Environment
     */
    void givingBirth() override;

    void acceptVisit(Visitor& v) override;

    /*!
     * @brief Checks whether the Wolf is free to move
     *
     * @return always true
     */
    bool isFreeToMove() const override;

    /*!
     * @brief Gets the Wolf herd id
     *
     * @return always -1 -- no herd for now.
     */
    int getHerdId() const override;

    bool canInfect(LivingEntity const * other) const override;

    virtual bool infectableBy(Wolf const * sheep) const override;

};

#endif // INFOSV_WOLF_HPP
