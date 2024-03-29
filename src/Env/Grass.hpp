#ifndef INFOSV_GRASS_HPP
#define INFOSV_GRASS_HPP

#include <Env/LivingEntity.hpp>
/*!
 * @class Grass
 *
 * @brief Represent a Grass food ressource in the simulation. Its size is equivalent
 * to it's energy level.
 */
class Grass : public LivingEntity
{
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
     * @brief Checks if a LivingEntity is eatable by the current Grass using
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

    /*!
     * @brief Checks if a LivingEntity is matable by the current Grass using
     * the canMate methods
     *
     * @param other the LivingEntity to check
     *
     * @return True if the  LivingEntity is matable
     */
    bool matable(LivingEntity const* other) const override;

    /*!
     * @brief Checks if this Grass can mate a Wolf
     *
     * @param wolf the Wolf
     *
     * @return False
     */
    bool canMate(Wolf const* wolf) const override;

    /*!
     * @brief Checks if this Grass can mate a Sheep
     *
     * @param sheep the Sheep
     *
     * @return False
     */
    bool canMate(Sheep const* sheep) const override;

    /*!
     * @brief Checks if this Grass can mate a Grass
     *
     * @param grass the other Grass
     *
     * @return False
     */
    bool canMate(Grass const* grass) const override;

    /*!
     * @brief Breeds the Grass with the given entity.
     *
     * @param entity the LivingEntity mate with
     */
    void meet(LivingEntity* mate) override;

    /*!
     * @brief Doesn't do anything as GRass can't mate.
     *
     * @param wolf the Wolf to mate with.
     */
    void breed(Wolf* wolf) override;

    /*!
     * @brief Doesn't do anything as GRass can't mate.
     *
     * @param sheep the Sheep to mate with.
     */
    void breed(Sheep* sheep) override;

    /*!
     * @brief Doesn't do anything as GRass can't mate.
     *
     * @param grass the Grass to mate with
     */
    void breed(Grass* grass) override;

    virtual void acceptVisit(Visitor& v) override;

    std::string getStatLabel() const override;

};

#endif // INFOSV_GRASS_HPP
