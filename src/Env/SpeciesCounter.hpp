#include <Env/Visitor.hpp>
#include <Utility/Constants.hpp>

class SpeciesCounter: public Visitor
{
private:
	int sheep, wolves, grass;

public:
	SpeciesCounter();
	virtual void visit(Wolf* e) override;
	virtual void visit(Sheep* e) override;
	virtual void visit(Grass* e) override;
	std::unordered_map<std::string, double> getCount() const;
};