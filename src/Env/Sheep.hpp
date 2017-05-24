#ifndef INFOSV_SHEEP_HPP
#define INFOSV_SHEEP_HPP

#include <Env/Animal.hpp>
/*!
 * @class Sheep
 *
 * @brief Represent a Sheep in the simulation.
 */
class Sheep : public Animal
{
public:
    /*!
     * @brief Constructor.
     *
     * @param initPos the Sheep's initial position
     * @param mother Mother's genome of the Sheep
     * @param father Father's genome of the Sheep
     */
    Sheep(const Vec2d& initPos, int herd = 0, Genome *mother = nullptr, Genome *father = nullptr);

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

    /*!
     * @brief Feeds the Sheep with the given entity, to regain energy and
     * decrease the entity's energy.
     *
     * @param entity the LivingEntity to be eaten
     *
     * @return the energy left in the entity after the Sheep ate it.
     */
    double feed(LivingEntity *entity) override;

    /*!
     * @brief Checks if a LivingEntity is matable by the current sheep using
     * the canMate methods
     *
     * @param other the LivingEntity to check
     *
     * @return True if the  LivingEntity is matable
     */
    bool matable(LivingEntity const* other) const override;

    /*!
     * @brief Checks if this Sheep can mate a Wolf
     *
     * @param wolf the Wolf
     *
     * @return False
     */
    bool canMate(Wolf const* wolf) const override;

    /*!
     * @brief Checks if this Sheep can mate a Sheep
     *
     * @param sheep the Sheep
     *
     * @return True if the two Sheep are of opposite sex.
     */
    bool canMate(Sheep const* sheep) const override;

    /*!
     * @brief Checks if this Sheep can mate a Grass
     *
     * @param grass the Grass
     *
     * @return False
     */
    bool canMate(Grass const* grass) const override;

    /*!
     * @brief Breeds the Sheep with the given entity.
     *
     * @param mate the LivingEntity to mate with
     */
    void meet(LivingEntity* mate) override;

    /*!
     * @brief Doesn't do anything as Sheep can't mate with Wolfs.
     *
     * @param wolf the Wolf to mate with.
     */
    void breed(Wolf* wolf) override;

    /*!
     * @brief Breeds the Sheep with the given Sheep.
     *
     * @param sheep the Sheep to mate with.
     */
    void breed(Sheep* sheep) override;

    /*!
     * @brief Doesn't do anything as Sheep can't mate with Grass.
     *
     * @param grass the Grass to mate with
     */
    void breed(Grass* grass) override;

    /*!
     * @brief Give birth to children, adding new Sheep to the Environment
     */
    void givingBirth() override;

    void acceptVisit(Visitor& v) override;

    /*!
     * @brief Gets the Sheep herd id
     */
    int getHerdId() const override;

    /*!
     * @brief Gets the leader of the Sheep
     */
    const Sheep* getLeader() const;

    /*!
     * @brief Checks whether the Sheep has a leader
     */
    bool hasLeader() const;

    /*!
     * @brief Checks whether the Sheep is a leader
     */
    bool isLeader() const;

    /*!
     * @brief Checks whether the Sheep is free to move
     *
     * @return true is sheep can move freely
     */
    bool isFreeToMove() const override;

    void drawOn(sf::RenderTarget& targetWindow) const override;

    std::string getDebugString() const override;

    bool canInfect(LivingEntity const * other) const override;

    virtual bool infectableBy(Sheep const * sheep) const override;

private:
    int herdId;

};

#endif // INFOSV_SHEEP_HPP
