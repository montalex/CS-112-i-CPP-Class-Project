#include <Genetics/ImmuneSystem.hpp>
#include <Application.hpp>
#include <Env/Animal.hpp>
#include <Random/Random.hpp>

ImmuneSystem::ImmuneSystem(const Animal* host_animal)
	: health(getAppConfig().immune_health_max),
	  activationLevel(getAppConfig().immune_adaptive_baseline),
	  host(host_animal), virus(nullptr)
{
	for (size_t i = 0; i < immuneProfile.size(); ++i) {
		immuneProfile[i] = host_animal->getGenome()->getImmuneGenes(i);
	}
}

double ImmuneSystem::getHealth() const {
	return health;
}

void ImmuneSystem::updateActivationLevel(sf::Time dt) {
	if (isInfected()) {
		activationLevel *= (1 + dt.asSeconds() * (0.5 * (1 - activationLevel*activationLevel / 16.0)));
	} else {
		double possibleLevel = activationLevel * 0.995;
		activationLevel = possibleLevel > getAppConfig().immune_adaptive_baseline ? possibleLevel : activationLevel;
	}
}

void ImmuneSystem::adaptToVirus(sf::Time dt) {
	for (size_t i = 0; i < immuneProfile.size(); ++i) {
		immuneProfile[i] += virus->getProfile().at(i) * dt.asSeconds() * 0.1;
	}
}

double ImmuneSystem::computeInfectionScore() const {
	double score = 0;
	double tmp = 0;
	// Compute the two sums at the same time. Possible as they are independent (except score+=)
	for (size_t i = 0; i < immuneProfile.size(); ++i) {
		score += immuneProfile[i] * virus->getProfile().at(i);
		tmp += getAppConfig().immune_defense_effectiveness * (host->getGenome()->getImmuneGenes(i) * virus->getProfile().at(i) +
				uniform(-getAppConfig().immune_defense_random_variability, getAppConfig().immune_defense_random_variability));
	}
	score *= getAppConfig().immune_defense_effectiveness;
	score += tmp;
	score = score*score * activationLevel;
	return score;
}

void ImmuneSystem::fightInfection(sf::Time dt) {
	health -= (getAppConfig().immune_health_penalty * virus->getAmount() * dt.asSeconds());
	virus->reduceAmount(computeInfectionScore() * dt.asSeconds());
}

void ImmuneSystem::update(sf::Time dt) {
	updateActivationLevel(dt);
	if (isInfected()) {
		virus->update(dt);
		adaptToVirus(dt);
		fightInfection(dt);
		if (virus->isDead()) {
        	std::cout << "VIRUS IS DEAD " << std::endl;
        	delete virus;
			virus = nullptr;
		}
	} else {
		double tmpHealth = health + getAppConfig().immune_health_recovery * dt.asSeconds();
		health = tmpHealth < getAppConfig().immune_health_max ? tmpHealth : health;
	}
}

bool ImmuneSystem::isInfected() const {
	return virus != nullptr;
}

Virus* ImmuneSystem::getVirus() const {
	return virus;
}

double ImmuneSystem::getActivationLevel() const {
	return activationLevel;
}

void ImmuneSystem::infect(Virus* v) {
	// Each animal has its own infection, virus object should not be shared.
	virus = new Virus(*v);
}

ImmuneSystem::~ImmuneSystem() {
	if (isInfected()) {
		delete virus;
	}
}
