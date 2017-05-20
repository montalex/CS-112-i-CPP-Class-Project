#include <Genetics/ImmuneSystem.hpp>
#include <Application.hpp>
#include <Env/Animal.hpp>
#include <Random/Random.hpp>

ImmuneSystem::ImmuneSystem(const Animal* host_animal)
	: health(getAppConfig().immune_health_max),
	  activationLevel(getAppConfig().immune_adaptive_baseline),
	  host(host_animal), virus(nullptr) {}

double ImmuneSystem::getHealth() const {
	return health;
}

void ImmuneSystem::updateActivationLevel(sf::Time dt) {
	if (isInfected()) {
		activationLevel *= 1 + dt.asSeconds() * (0.5 * (1 - activationLevel*activationLevel / 16));
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
	for (size_t i = 0; i < immuneProfile.size(); ++i) {
		score += immuneProfile[i] * virus->getProfile().at(i);
	}
	double tmp = 0;
	for (size_t i = 0; i < immuneProfile.size(); ++i) {
		tmp += getAppConfig().immune_defense_effectiveness * 
			(host->getGenome()->getImmuneGenes(i) * virus->getProfile().at(i) + uniform(0.0, getAppConfig().immune_defense_random_variability));
	}
	score += tmp;
	score = score*score * activationLevel;
	return score;
}

void ImmuneSystem::fightInfection(sf::Time dt) {
	health -= getAppConfig().immune_health_penalty * virus->getAmount() * dt.asSeconds();
	virus->reduceAmount(computeInfectionScore() * dt.asSeconds());
}

void ImmuneSystem::update(sf::Time dt) {
	updateActivationLevel(dt);
	if (isInfected()) {
		virus->update(dt);
		adaptToVirus(dt);
		fightInfection(dt);
		if (virus->isDead()) {
			virus = nullptr;
		}
	} else {
		double tmpHealth = getAppConfig().immune_health_recovery * dt.asSeconds();
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
	virus = v;
}

void ImmuneSystem::setImmuneGenes(const std::array<double, 10>& immuneProfile) {
	this->immuneProfile = immuneProfile; // copy constructor
}