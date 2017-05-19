#include <Genetics/Infecter.hpp>
Infecter::Infecter(Virus* v) : virus(v) {}

void Infecter::visit(Wolf* e) {
	e->infect(virus);
}
void Infecter::visit(Sheep* e) {
	e->infect(virus);
}
void Infecter::visit(Grass* e) {}
