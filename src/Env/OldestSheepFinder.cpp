#include <Env/OldestSheepFinder.hpp>

OldestSheepFinder::OldestSheepFinder(int herd)
	: oldestAge(sf::seconds(0)), herdId(herd)
{}

 const Sheep* OldestSheepFinder::getOldestVisited() {
 	if (oldest == nullptr) {
        std::cout << "return nullptr" << std::endl;
 	}
 	if (!oldest) {
 		std::cout << "return nullptr2" << std::endl;
 	}
    return oldest;
 }

void OldestSheepFinder::visit(Wolf* e) {}

void OldestSheepFinder::visit(Grass* e) {}

void OldestSheepFinder::visit(Sheep* e) {

	if (!e->isDead() && e->getHerdId() == herdId && e->getAge() > oldestAge) {
        oldestAge = e->getAge();
        oldest = e;
    }
}
