#include <Interface/Visitor.hpp>

class Infecter: public Visitor {
public:
	Infecter(Virus* v);
	void visit(Wolf* e);
	void visit(Sheep* e);
	void visit(Grass* e);
private:
	Virus* virus;
};