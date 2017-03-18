#include <list>
#include <Env/Animal.hpp>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>

/* Represents the simulation's Environment
 *
 * list<Animal> animals: the animal population in the Environment
 * list<Target> targets: position of existing ressources in the Environment
 */
class Environment {
        private:
                std::list<Animal> animals;
                std::list<Vec2d> targets;

        public:
                //Using default constructor
                //Adds an animal to the Environment
                void addAnimal(Animal* animal);
                //Adds a target to the Environment
                void addTarget(const Vec2d& target);
                //Updates the Environment every tick of time
                void update(sf::Time dt);
                //Draws Environment on given targetWindow
                void drawOn(sf::RenderTarget& targetWindow) const;
                //Resets and empties the Environment
                void reset();
};
