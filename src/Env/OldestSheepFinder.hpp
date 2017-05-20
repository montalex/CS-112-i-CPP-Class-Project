#include <Env/Wolf.hpp>
#include <Env/Sheep.hpp>
#include <Env/Grass.hpp>
#include <Interface/Visitor.hpp>

/*!
 * @class OldestSheepFinder
 *
 * @brief Visitor used to iterate over the entities in order to
          find a new herd leader for the sheep
 */
class OldestSheepFinder : public Visitor {
private:
    const Sheep* oldest;
    sf::Time oldestAge;
    int herdId;

public:
	/*!
	 * @brief Constructs new object
	 *
	 * @param herd The id of the herd whose new leader needs to be
	          elected
	 */
    OldestSheepFinder(int herd);

    /*!
     * @brief Gets pointer to the oldest sheep of the herd amongst the
              the visited ones
     */
    const Sheep* getOldestVisited();
    void visit(Wolf* e) override;
    void visit(Grass* e) override;
    void visit(Sheep* e) override;
};