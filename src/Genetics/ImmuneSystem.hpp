#ifndef INFOSV_IMMUNE
#define INFOSV_IMMUNE

#include <Genetics/Virus.hpp>
#include <Interface/Updatable.hpp>
#include <array>

class Animal;

class ImmuneSystem: public Updatable {
private:
	double health;
	double activationLevel;
	const Animal* host;
	Virus* virus;
	std::array<double, 10> immuneProfile;

	void updateActivationLevel(sf::Time dt);
	void adaptToVirus(sf::Time dt);
	void fightInfection(sf::Time dt);
public:
	ImmuneSystem(const Animal* host_animal);
	double getHealth() const;
    void update(sf::Time dt) override;
    bool isInfected() const;
    Virus* getVirus() const;
	double computeInfectionScore() const;
	double getActivationLevel() const;
	void infect(Virus* v);
};

#endif