#include <Env/SpeciesCounter.hpp>

SpeciesCounter::SpeciesCounter(): sheep(0), wolves(0), grass(0), infected(0) {}

void SpeciesCounter::visit(Wolf* e)
{
    wolves++;
    if (e->isInfected()) infected++;
}

void SpeciesCounter::visit(Sheep* e)
{
    sheep++;
    if (e->isInfected()) infected++;
}

void SpeciesCounter::visit(Grass* e)
{
    grass++;
}

std::unordered_map<std::string, double> SpeciesCounter::getCount() const
{
    return {
        {s::WOLVES, wolves},
        {s::GRASS, grass},
        {s::SHEEP, sheep},
        {s::INFECTED, infected}
    };
}
