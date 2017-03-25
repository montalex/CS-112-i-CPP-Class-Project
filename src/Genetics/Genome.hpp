#ifndef INFOSV_GENOME_HPP
#define INFOSV_GENOME_HPP

#include <stdlib.h>
#include <Random/Random.hpp>
#include <iostream>
#include <Utility/Utility.hpp>

#define colorSize 2
#define immuneSize 10

/*!
 * @class Genome
 *
 * @brief Represents all animal's genome in the simulation
 *
 * Sex sex: the Genome's gender
 * ColorAllele color: the Genome's color attributes
 * double immuneProfile: the Genome's immune system profile
 */
class Genome {
    public:
        /*!
         * @brief Constructor.
         *
         * @param mother the Genome's mother
         * @param father the Genome's father
         */
        Genome(Genome *mother = nullptr, Genome *father = nullptr);

        /*!
         * @brief Gets the Genome's sex.
         *
         * @return the sex of the Genome (Sex enum)
         */
        Sex getSex() const;

        /*!
         * @brief Gets the Genome's first color attribute.
         *
         * @return the first color of the Genome (ColorAllele enum)
         */
        ColorAllele getFirstColorAllele() const;

        /*!
         * @brief Gets the Genome's second color attribute.
         *
         * @return the second color of the Genome (ColorAllele enum)
         */
        ColorAllele getSecondColorAllele() const;

        /*!
         * @brief Gets the Genome's visible color.
         *
         * @return the visible color of the Genome (ColorAllele enum)
         */
        ColorAllele getColorPhenotype() const;

        /*!
         * @brief Gets the Genome's immune profile
         *
         * @return the Genome's immune profile (double)
         */
        double getImmuneGenes(size_t idx) const;

        /*!
         * @brief Priting method for << operator
         *
         * @param out the output stream
         *
         * @return the output stream (ostream)
         */
        std::ostream& print(std::ostream& out) const;

    private:
        Sex sex;
        ColorAllele color[colorSize];
        double immuneProfile[immuneSize];
};

/*!
 * @brief Operator for printing Genome.
 *
 * @param out the output stream
 * @param g the other Genome
 *
 * @return the output stream (ostream)
 */
std::ostream& operator<<(std::ostream& out, const Genome& g);

#endif // INFOSV_GENOME_HPP
