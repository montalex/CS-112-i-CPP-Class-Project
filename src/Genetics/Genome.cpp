#include <Genetics/Genome.hpp>

Genome::Genome(Genome *mother, Genome *father) {
        if(INFOSV_RANDOM_HPP::bernoulli(0.5)) {
                sex = MALE;
        } else {
                sex = FEMALE;
        }

        if(mother != nullptr && father != nullptr) {
                if(INFOSV_RANDOM_HPP::bernoulli(0.5)) {
                        color[0] = mother->color[0];
                } else {
                        color[0] = mother->color[1];
                }

                if(INFOSV_RANDOM_HPP::bernoulli(0.5)) {
                        color[1] = father->color[0];
                } else {
                        color[1] = father->color[1];
                }

                for(int i = 0; i < immuneSize; i++) {
                        double tempValue = 0.0;
                        if(INFOSV_RANDOM_HPP::bernoulli(0.5)) {
                                tempValue = mother->immuneProfile[i];
                        } else {
                                tempValue = father->immuneProfile[i];
                        }
                        tempValue += INFOSV_RANDOM_HPP::uniform(-0.3, 0.3);
                        immuneProfile[i] = tempValue;
                }
        } else {
                for(int i = 0; i < colorSize; i++) {
                        if(INFOSV_RANDOM_HPP::bernoulli(0.3)) {
                                color[i] = BLACK;
                        } else {
                                color[i] = WHITE;
                        }
                }

                for(int i = 0; i < immuneSize; i++) {
                        immuneProfile[i] = INFOSV_RANDOM_HPP::uniform(-5.0, 5.0);
                }
        }
}

Sex Genome::getSex() const {
        return sex;
}

ColorAllele Genome::getFirstColorAllele() const {
        return color[0];
}

ColorAllele Genome::getSecondColorAllele() const {
        return color[1];
}

ColorAllele Genome::getColorPhenotype() const {
        if(getFirstColorAllele() == BLACK && getSecondColorAllele() == BLACK) {
                return BLACK;
        } else {
                return WHITE;
        }
}

double Genome::getImmuneGenes(size_t idx) const {
        return immuneProfile[idx];
}

std::ostream& Genome::print(std::ostream& out) const {
        out << "Genome (" << sexToString() << ")" << std::endl;
        out << "Color phenotype = " << colorAlleleToString(getColorPhenotype()) << std::endl;
        out << "First color allele = " << colorAlleleToString(getFirstColorAllele()) << std::endl;
        out << "Second color allele = " << colorAlleleToString(getSecondColorAllele()) << std::endl;
        out << "Immune profile = ";
        for(int i = 0; i < immuneSize; i++) {
                out << getImmuneGenes(i) << " ";
        }
        out << std::endl;
        return out;
}

std::string Genome::sexToString() const {
        switch(sex) {
                case MALE:
                        return "male";
                case FEMALE:
                default:
                        return "female";
        }
}

std::ostream& operator<<(std::ostream& out, const Genome& g) {
        g.print(out);
        return out;
}
