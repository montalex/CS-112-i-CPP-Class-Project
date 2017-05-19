#ifndef INFOSV_ENVIRONMENT_HPP
#define INFOSV_ENVIRONMENT_HPP

#include <list>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>
#include <Env/Sheep.hpp>
#include <Env/Wolf.hpp>

class Animal;
class LivingEntity;

/*!
 * @class Environment
 *
 * @brief Represents the simulation's Environment.
 *
 * list<LivingEntity> entities: the entity population in the Environment
 */
class Environment
{

public:
    //Using default constructor for now

    /*!
     * @brief Destructor
     */
    ~Environment();

    /*!
     * @brief Adds an entity to the Environment.
     *
     * @param entity the new LivingEntity
     */
    void addEntity(LivingEntity* entity);

    /*!
     * @brief Removes an entity to the Environment and destroys it.
     *
     * @param entity the LivingEntity to remove
     */
    void removeEntity(LivingEntity* entity);

    /*!
     * @brief Updates the Environment through time.
     *
     * @param dt the time passed
     */
    void update(sf::Time dt);

    /*!
     * @brief Draws the Environment in the given window.
     *
     * @param targetWindow the window to draw on
     */
    void drawOn(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief Resets and empties the Environment.
     */
    void reset();

    /*!
     * @brief Gets all entities that the given Animal see in the Environment.
     *
     * @param animal the Animal
     *
     * @return all entities that the Animal sees
     */
    std::list<LivingEntity*> getEntitiesInSightForAnimal(const Animal* animal) const;

    /*!
     * @brief Computes new data for graphs.
     *
     * @param label the label of the graph that will be receive the data.
     *
     * @return new data to add to the graph.
     */
    std::unordered_map<std::string, double> fetchData(std::string const & label);

    /*!
     * @brief Gets the leader of the sheep
     *
     * @param id The sheep
     * @return pointer to the animal leader.
     */
    const Sheep* getLeader(int herdId) const;

    /*!
     * @brief Adds the sheep to its herd or creates a new one if none exist
     * with the animal herd id
     *
     * @param sheep the sheep to add to the herd.
    */
    void addToHerd(const Sheep* const sheep);

    /*!
     * @brief Gets all entities that the given Animal wants to avoid.
     *
     * @param animal the Animal
     *
     * @return all entities that the Animal wants to avoid
     */
    std::list<LivingEntity*> getNearbyAvoidableEntitesForAnimal(const Animal* animal) const;

    /*!
     * @brief Provides pointer to currently tracked entity
     */
    const LivingEntity* getTrackedEntity() const;

    /*!
     * @brief Tracks the entity which is the closest to the provided position.
     * 
     * @param position the position of the entity to track.
     */
    void trackEntity(Vec2d position);

    /*!
     * @brief Stops tracking any entity.
     */
    void stopTrackingAnyEntity();

    void infectEntity(const Vec2d& p, Virus* v);

private:
    void updateHerds();
    const Sheep* findOldestSheep(int herd);
    std::list<LivingEntity*> entities;
    std::unordered_map<int, const Sheep*> sheepLeaders;
    const LivingEntity* tracked = nullptr;

    LivingEntity* entityClosestTo(const Vec2d& position);
};
#endif // INFOSV_ENVIRONMENT_HPP
