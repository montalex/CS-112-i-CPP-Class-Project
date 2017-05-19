#ifndef INFOSV_VIRUS
#define INFOSV_VIRUS

#include <array>
#include <Interface/Updatable.hpp>

class Virus: public Updatable {
private:
	double amount;
	double growthRate;
	std::array<double, 10> virulence;

public:
	Virus();
	Virus(const Virus& other);
	Virus(const std::array<double, 10>& virulence_profile);
    void update(sf::Time dt) override;
    const std::array<double, 10>& getProfile() const;
    double getAmount() const;
    bool isDead() const;
    void reduceAmount(double difference);
};

#endif