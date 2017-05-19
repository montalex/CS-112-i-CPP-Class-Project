#include <Genetics/Virus.hpp>
#include <Application.hpp>
#include <Random/Random.hpp>

Virus::Virus() : amount(0), growthRate(getAppConfig().virus_growth_rate)
{
	for (size_t i = 0; i < VIRULENCE_PROFILE_SIZE; ++i) {
		virulence[i] = bernoulli(getAppConfig().virus_sparsity) ? uniform(-5, 5) : 0;
	}
}

Virus::Virus(const Virus& other) : amount(other.amount), growthRate(other.growthRate)
{
	for (size_t i = 0; i < VIRULENCE_PROFILE_SIZE; ++i) {
		virulence[i] = other.virulence[i];
	}
}

Virus::Virus(const double * virulence_profile) : amount(0), growthRate(getAppConfig().virus_growth_rate)
{
	for (size_t i = 0; i < VIRULENCE_PROFILE_SIZE; ++i) {
		virulence[i] = virulence_profile[i];
	}
}
