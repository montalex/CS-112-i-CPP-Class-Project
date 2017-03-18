#include <Env/Environment.hpp>

void Environment::addAnimal(Animal* animal) {
        animals.push_back(*animal);
}

void Environment::addTarget(const Vec2d& target) {
        //Maybe change this target reference with pointer later!
        targets.push_back(target);
}

void Environment::update(sf::Time dt) {
        //TODO: This method will be implemented in later steps
        //faire évoluer les animaux de la faune ici
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const {

        sf::CircleShape circle;
        sf::Color red = sf::Color(255, 0, 0);
        for(auto& target: targets) {
                circle = buildCircle(target, 5.0, red);
                targetWindow.draw(circle);
        }
}

void Environment::reset() {
        for(size_t i = 0; i < animals.size(); i++) {
                animals.pop_back();
        }

        for(size_t i = 0; i < targets.size(); i++) {
                targets.pop_back();
        }
}
