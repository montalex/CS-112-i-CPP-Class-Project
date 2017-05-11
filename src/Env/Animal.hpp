#ifndef INFOSV_ANIMAL_HPP
#define INFOSV_ANIMAL_HPP

#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Config.hpp>
#include <Random/Random.hpp>
#include <Env/LivingEntity.hpp>
#include <Genetics/Genome.hpp>

/*!
 * @brief Represents an Animal state.
 */
enum AnimalState {
    FOOD_IN_SIGHT,
    FEEDING,
    RUNNING_AWAY,
    MATE_IN_SIGHT,
    MATING,
    GIVING_BIRTH,
    WANDERING,
    IDLE,
};

/*!
 * @class Animal
 *
 * @brief Represent an Animal in the simulation.
 *
 * Vec2d direction: the Animal's direction in the Animal's coordinate system.
 * Vec2d target: the Animal's target position
 * Vec2d virtual_target: the Animal's virtual target position in the Animal's
 *                       coordinate system.
 * double speedNorm: the norm of the Animal's speed.
 * double genome: the Animal's genetic material.
 * AnimalState state: the Animal's current state.
 * bool hungry: define if the Animal is hungry or not.
 * sf::Time feedingTime: the time during which the Animal is feeding.
 * sf::Time matingTime: the time during which the Animal is mating.
 * bool pregnant: define if the Animal is pregnant or not.
 * int nBabies: the amount of babies the Animal is having once pregnant.
 * sf::Time gestationTime: the time the Animal is pregnant before giving birth.
 */
class Animal : public LivingEntity
{
public:
    /*!
     * @brief Constructor.
     *
     * @param initPos the Animla's initial position
     * @param startEnergy the Animal's starting energy
     * @param mother Mother's genome of the Animal
     * @param father Father's genome of the Animal
     */
    Animal(const Vec2d& initPos, const double& startEnergy, Genome *mother = nullptr,
           Genome *father = nullptr, const sf::Time& gesTime = sf::seconds(0));

    /*!
     * @brief Destructor.
     */
    virtual ~Animal();

    /*!
     * @brief Gets the Animal's direction.
     *
     * @return the Animal's direction (Vec2d)
     */
    Vec2d getDirection() const;

    /*!
     * @brief Sets the Animal's direction.
     *
     * @param newDirection the new direction of the Animal
     */
    void setDirection(const Vec2d& newDirection);

    /*!
     * @brief Gets the Animal's target position.
     *
     * @return the Animal's target position (Vec2d)
     */
    Vec2d getTarget() const;

    /*!
     * @brief Sets the Animal's target position.
     *
     * @param target the new target position
     */
    void setTarget(const Vec2d& target);

    /*!
     * @brief Gets the Animal's speed norm.
     *
     * @return the Animal's speed norm (double)
     */
    double getSpeedNorm() const;

    /*!
     * @brief Sets the Animal's speed norm.
     *
     * @param newNorm the new speed norm
     */
    void setSpeedNorm(const double& newNorm);

    /*!
     * @brief Gets the Animal's genome.
     *
     * @return the Animal's genome (Genome)
     */
    Genome getGenome() const;

    /*!
     * @brief Gets the Animal's state.
     *
     * @return the Animal's state (AnimalState)
     */
    AnimalState getState() const;

    /*!
     * @brief Sets the Animal's state to the given state.
     *
     * @param newState the new state.
     */
    void setState(const AnimalState& newState);

    /*!
     * @brief Gets the Animal's feeding time.
     *
     * @return the Animal's feeding time (sf::Time)
     */
    sf::Time getFeedingTime() const;

    /*!
     * @brief Sets the Animal's feeding time.
     *
     * @param newTime the new feeding time.
     */
    void setFeedingTime(const sf::Time& newTime);

    /*!
     * @brief Gets the Animal's mating time.
     *
     * @return the Animal's mating time (sf::Time)
     */
    sf::Time getMatingTime() const;

    /*!
     * @brief Sets the Animal's mating time.
     *
     * @param newTime the new mating time.
     */
    void setMatingTime(const sf::Time& newTime);

    /*!
     * @brief Checks if the Animal is pregnant.
     *
     * @return True if the Animal is pregnant
     */
    bool isPregnant() const;

    /*!
     * @brief Sets the Animal's pregnancy state.
     *
     * @param preg the pregnancy state of the Animal
     */
    void setPregnant(const bool& preg);

    /*!
     * @brief Gets the number of babies the Animal will have.
     *
     * @return the amount of babies the Animal will have (int)
     */
    int getNBabies() const;

    /*!
     * @brief Sets the amount of babies the Animal will have.
     *
     * @param nbBabies the amount of babies the Animal will have
     */
    void setNBabies(const int& nbBabies);

    /*!
     * @brief Gets the Animal's gestation time.
     *
     * @return the Animal's gestation time (sf::Time)
     */
    sf::Time getGestationTime() const;

    /*!
     * @brief Sets the Animal's gestation time.
     *
     * @param newTime the new gestation time.
     */
    void setGestationTime(const sf::Time& newTime);

    /*!
     * @brief Updates the Animal's state according to its surrounding.
     */
    void updateState();

    /*!
     * @brief Gets the Animal's maximum speed according to its current state.
     *
     * @return the Animal's maximum speed (double)
     */
    double getMaxSpeed() const;

    /*!
     * @brief Gets the Animal's maximum speed.
     *
     * @return the Animal's maximum speed (double)
     */
    virtual double getStandardMaxSpeed() const = 0;

    /*!
     * @brief Gets the Animal's mass.
     *
     * @return the Animal's mass (double)
     */
    virtual double getMass() const = 0;

    /*!
     * @brief Get's the Animal's texture.
     *
     * @return the Animal's texture.
     */
    virtual sf::Texture& getTexture() const = 0;

    /*!
     * @brief Gets the Animal's speed vector.
     *
     * @return the Animal's speed vector (Vec2d)
     */
    Vec2d getSpeedVector() const;

    /*!
     * @brief Gets the Animal's view range in radians.
     *
     * @return the Animal's view range (double)
     */
    virtual double getViewRange() const = 0;

    /*!
     * @brief Gets the Animal's view distance.
     *
     * @return the Animal's view distance (double)
     */
    virtual double getViewDistance() const = 0;

    /*!
     * @brief Gets the Animal's view rotation.
     *
     * @return the Animal's view rotation (double)
     */
    double getRotation() const;

    /*!
     * @brief Sets the Animal's view rotation.
     *
     * @param angle the view rotation angle
     */
    void setRotation(const double& angle);

    /*!
     * @brief Gets the Animal's virtual target radius
     *
     * @return the Animal's virtual target radius (double)
     */
    virtual double getRandomWalkRadius() const = 0;

    /*!
     * @brief Gets the Animal's distance to his virtual target circle center
     *
     * @return the Animal's distance to his virtual target circle center
     *         (double)
     */
    virtual double getRandomWalkDistance() const = 0;

    /*!
     * @brief Gets the Animal's virtual target jitter
     *
     * @return the Animal's virtual target jitter (double)
     */
    virtual double getRandomWalkJitter() const = 0;

    /*!
     * @brief Updates the Animal's target and calls updatePosition to modify
     *        its attribute over time.
     *
     * @param dt the time passed
     */
    virtual void update(sf::Time dt) override;

    /*!
     * @brief Update the Animal's position, direction & speed norm over time
     *        according to its attraction force.
     *
     * @param dt the time passed
     * @param attractionForce the attraction force
     */
    void updatePosition(sf::Time dt, const Vec2d& attractionForce);

    /*!
     * @brief Draws the Animal and his target in the given window.
     *
     * @param targetWindow the window to draw on
     */
    void drawOn(sf::RenderTarget& targetWindow) const override;

    /*!
     * @brief Draws the Animal's vision in the given window.
     *
     * @param targetWindow the window to draw on
     */
    void drawVision(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Draws the Animal's virtual target in the given window.
     *
     * @param targetWindow the window to draw on
     */
    void drawVirtualTarget(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Draws the Animal's debug text, showing on the screen some of
     * his attributes.
     *
     * @param targetWindow the window to draw on
     */
    void drawDebugText(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Gets the Animal's attraction force to his target.
     *
     * @return Animal's attraction force to his target (Vec2d)
     */
    Vec2d attractionForce() const;

    /*!
     * @brief Gets the Deceleration constant for the Animal
     *        depending on the distance to his target.
     *
     * @param distanceToTarget the distance to the target
     *
     * @return the Deceleration coefficient (Deceleration enum)
     */
    Deceleration getDeceleration(const double& distanceToTarget) const;

    /*!
     * @brief Tests if target is in sight.
     *
     * @param target the target position
     *
     * @return True if target is in sight
     */
    bool isTargetInSight(const Vec2d& target) const;

    /*!
     * @brief Compute the Animal's random movement according to its virtual
     *        target and returns its attraction force.
     *
     * @return Vec2 the new attraction force
     */
    Vec2d randomWalk();

    /*!
     * @brief Converts a vector in Animal's coordinates in global coordinates.
     *
     * @param coordinates the vector to Converts
     *
     * @return the vector in global coordinates (Vec2d)
     */
    Vec2d convertToGlobalCoord(const Vec2d& coordinates) const;

    /*!
     * @brief Returns the debug string of this Animal to be print on screen.
     *
     * @return the debug string (std::string)
     */
    std::string getDebugString() const override;

    /*!
     * @brief Updates the Animal's hunger status.
     */
    void updateHunger();

    /*!
     * @brief Checks if the Animal is hungry.
     *
     * @return True if the Animal is hungry
     */
    bool isHungry() const;

    /*!
     * @brief Feeds the Animal with the given entity, to regain energy and
     * decrease the entity's energy.
     *
     * @param entity the LivingEntity to be eaten
     *
     * @return the energy left in the entity after the Animal ate it.
     */
    virtual double feed(LivingEntity *entity) = 0;

    /*!
     * @brief Checks if the Animal is a female.
     *
     * @return True if the Animal is a female
     */
    bool isFemale() const;

private:
    Vec2d direction;
    Vec2d target;
    Vec2d current_target;
    double speedNorm;
    Genome genome;
    AnimalState state;
    bool hungry;
    sf::Time feedingTime;
    sf::Time matingTime;
    bool pregnant;
    int nBabies;
    sf::Time gestationTime;
};

/*!
 * @brief Converts the given Animal's state to a string.
 *
 * @param  animal the Animal which state is to be converted
 *
 * @return the string description of the state (std::string)
 */
std::string stateToString(const AnimalState state);

#endif // INFOSV_ANIMAL_HPP
