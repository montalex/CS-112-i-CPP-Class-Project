#include <Genetics/Virus.hpp>
#include <Application.hpp>
#include <Random/Random.hpp>

Virus::Virus() : amount(0), growthRate(getAppConfig().virus_growth_rate)
{
	for (size_t i = 0; i < virulence.size(); ++i) {
		virulence[i] = bernoulli(getAppConfig().virus_sparsity) ? uniform(-5, 5) : 0;
	}
}

Virus::Virus(const Virus& other) : amount(other.amount), growthRate(other.growthRate)
{
	virulence = other.virulence; // = operator calls copy constructor.
}

Virus::Virus(const std::array<double, 10>& virulence_profile) : amount(0), growthRate(getAppConfig().virus_growth_rate)
{
	virulence = virulence_profile;  // = operator calls copy constructor.
}

void Virus::update(sf::Time dt) {
	amount *= (1 + growthRate * (1 - amount / getAppConfig().virus_max) * dt.asSeconds());
}

const std::array<double, 10>& Virus::getProfile() const {
  	return virulence;
}

double Virus::getAmount() const {
	return amount;
}

bool Virus::isDead() const {
	return amount <= getAppConfig().virus_initial_quantity;
}

void Virus::reduceAmount(double difference) {
	amount -= difference;
}