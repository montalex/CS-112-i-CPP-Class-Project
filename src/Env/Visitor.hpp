
#include <Env/Wolf.hpp>
#include <Env/Sheep.hpp>
#include <Env/Grass.hpp>
/*class Wolf;
class Sheep;
class Grass;*/
#include <Env/LivingEntity.hpp>
/*!
 * Abstract class for visitor.
 */
class Visitor
{
public:
	virtual void visit(Wolf* e) = 0;
	virtual void visit(Sheep* e) = 0;
	virtual void visit(Grass* e) = 0;
};