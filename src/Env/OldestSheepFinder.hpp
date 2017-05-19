#include <Env/Wolf.hpp>
#include <Env/Sheep.hpp>
#include <Env/Grass.hpp>
#include <Interface/Visitor.hpp>

class OldestSheepFinder : public Visitor {
private:
    const Sheep* oldest;
    sf::Time oldestAge;
    int herdId;

public:
    OldestSheepFinder(int herd);

    const Sheep* getOldestVisited();
    void visit(Wolf* e) override;
    void visit(Grass* e) override;
    void visit(Sheep* e) override;
};