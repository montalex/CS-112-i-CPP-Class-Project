#ifndef INFOSV_VIRUS
#define INFOSV_VIRUS

#include <array>
#include <Interface/Updatable.hpp>

/*!
 * @class Virus
 *
 * @brief Represents a population of virus
 */
class Virus: public Updatable
{
private:
    double amount;
    double growthRate;
    std::array<double, 10> virulence;

public:
    Virus();
    Virus(const Virus& other);

    /*!
     * @brief Creates a virus given a virulence profile
     */
    Virus(const std::array<double, 10>& virulence_profile);

    void update(sf::Time dt) override;

    /*!
     * @brief Getter for the virulence profile
     */
    const std::array<double, 10>& getProfile() const;

    /*!
     * @brief Getter for the quantity of viruses
     */
    double getAmount() const;

    /*!
     * @brief Checks whether the virus population is extinct
     */
    bool isDead() const;

    /*!
     * @brief Kills a part of the population
     *
     * @param the number of viruses to deduct from the current population
     */
    void reduceAmount(double difference);

    /*!
     * @brief Provides a string representation of the virus population
     */
    std::string toString() const;
};

std::ostream& operator<<(std::ostream& os, Virus const & v);

#endif