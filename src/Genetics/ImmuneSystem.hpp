#ifndef INFOSV_IMMUNE
#define INFOSV_IMMUNE

#include <Genetics/Virus.hpp>
#include <Interface/Updatable.hpp>
#include <array>

class Animal;

/*!
 * @class ImmuneSystem
 *
 * @brief Represents the immune system of an animal
 */
class ImmuneSystem: public Updatable {
private:
	double health;
	double activationLevel;
	const Animal* host;
	Virus* virus;
	std::array<double, 10> immuneProfile;

	/*!
	 * @brief Updates the activation level of the system
	 */
	void updateActivationLevel(sf::Time dt);

	/*!
	 * @brief The immune system adapts itself to the virus it is fighting.
	 */
	void adaptToVirus(sf::Time dt);

	/*!
	 * @brief Computes the evolution of the fight between virus and immune system.
	 */
	void fightInfection(sf::Time dt);

public:
	ImmuneSystem(const Animal* host_animal);

	~ImmuneSystem();

	/*!
	 * @brief Health getter
	 */
	double getHealth() const;

    void update(sf::Time dt) override;

    /*!
     * @brief Checks whether the immune system is fighting an infection or not.S
     */
    bool isInfected() const;

    /*!
     * @brief Gets pointer to the instance of the virus to fight.
     */
    Virus* getVirus() const;

    /*!
     * @brief Computes the infection score
     */
	double computeInfectionScore() const;

	/*!
	 * @brief Activation level getter
	 */
	double getActivationLevel() const;

	/*!
	 * @brief The immune sytem has to fight the new virus
	 *
	 * @param v The virus to fight.
	 */
	void infect(Virus* v);
};

#endif