#include <Env/OldestSheepFinder.hpp>

OldestSheepFinder::OldestSheepFinder(int herd)
	: oldest(nullptr), oldestAge(sf::seconds(0)), herdId(herd)
{}

 const Sheep* OldestSheepFinder::getOldestVisited() {
	std::cout << "GET OLDEST VISITED"  << std::endl;
    return oldest;
 }

void OldestSheepFinder::visit(Wolf* e) {}

void OldestSheepFinder::visit(Grass* e) {}

void OldestSheepFinder::visit(Sheep* e) {
	if (!e->isDead() && e->getHerdId() == herdId && e->getAge() > oldestAge) {
		std::cout << "GET OLDER"  << std::endl;
        oldestAge = e->getAge();
        oldest = e;
    }
}
