#include <stdlib.h>
#include <Random/Random.hpp>
#include <iostream>
#include <Utility/Utility.hpp>

#define colorSize 2
#define immuneSize 10

/* Represents all animal's genome in the simulation
 *
 * Sex sex: the Genome's gender
 * ColorAllele color: the Genome's color attributes
 * double immuneProfile: the Genome's immune system profile
 */
class Genome {
        private:
                Sex sex;
                ColorAllele color[colorSize];
                double immuneProfile[immuneSize];
        public:
                //Constructor
                Genome(Genome *mother = nullptr, Genome *father = nullptr);
                //Returns the sex of the Genome
                Sex getSex() const;
                //Returns the Genome's first color allele
                ColorAllele getFirstColorAllele() const;
                //Returns the Genome's second color allele
                ColorAllele getSecondColorAllele() const;
                //Returns the Genome's visible color
                ColorAllele getColorPhenotype() const;
                //Returns the idx-th element of the Genome's immune profil
                double getImmuneGenes(size_t idx) const;
                //Printing method for << operator
                std::ostream& print(std::ostream& out) const;
                //Returns the Genome's gender as a string
                std::string sexToString() const ;
};

//Redefine operator << to be used with Genome.
std::ostream& operator<<(std::ostream& out, const Genome& g);
