#include <list>
#include <Env/Animal.hpp>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>

/*!
 * @class Environment
 *
 * @brief Represents the simulation's Environment.
 *
 * list<Animal> animals: the animal population in the Environment
 * list<Target> targets: position of existing ressources in the Environment
 */
class Environment {

    public:
        //Using default constructor for now

        /*!
         * @brief Adds an Animal to the Environment.
         *
         * @param animal the new Animal
         */
        void addAnimal(Animal* animal);

        /*!
         * @brief Adds a Target to the Environment.
         *
         * @param target the new target position
         */
        void addTarget(const Vec2d& target);

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

    private:
        std::list<Animal> animals;
        std::list<Vec2d> targets;
};
