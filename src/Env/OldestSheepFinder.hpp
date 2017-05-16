#include <Env/Wolf.hpp>
#include <Env/Sheep.hpp>
#include <Env/Grass.hpp>
#include <Env/Visitor.hpp>

class OldestSheepFinder : public Visitor {
private:
    const Sheep* oldest;
    sf::Time oldestAge;
    int herdId;

public:
    OldestSheepFinder(int herd);

    const Sheep* getOldestVisited();
    virtual void visit(Wolf* e) override;
    virtual void visit(Grass* e) override;
    virtual void visit(Sheep* e) override;
};