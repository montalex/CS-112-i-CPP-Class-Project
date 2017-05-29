#include <Genetics/Infecter.hpp>
Infecter::Infecter(Virus* v) : virus(v) {}

void Infecter::visit(Wolf* e)
{
    if (!e->hasVirus()) e->infect(virus);
}
void Infecter::visit(Sheep* e)
{
    if (!e->hasVirus()) e->infect(virus);
}
void Infecter::visit(Grass* e) {}
