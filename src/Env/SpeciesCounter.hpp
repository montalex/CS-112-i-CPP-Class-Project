#include <Interface/Visitor.hpp>
#include <Utility/Constants.hpp>

/*!
 * @class SpeciesCounter
 * @brief Simple implementation of the visitor
 * super class to count the number of sheep, wolves and grass
 * entities given a list of LivingEntities
 */
class SpeciesCounter: public Visitor
{
private:
	int sheep, wolves, grass;

public:
	SpeciesCounter();
	void visit(Wolf* e) override;
	void visit(Sheep* e) override;
	void visit(Grass* e) override;
	std::unordered_map<std::string, double> getCount() const;
};
