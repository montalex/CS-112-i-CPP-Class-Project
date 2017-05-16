#ifndef INFOSV_VISITOR
#define INFOSV_VISITOR

#include <Env/Wolf.hpp>
#include <Env/Sheep.hpp>
#include <Env/Grass.hpp>
#include <Env/LivingEntity.hpp>
/*!
 * @class Visitor
 * @brief Abstract class for visitor over the LivingEntity
 * class hierarchy
 */
class Visitor
{
public:
	virtual void visit(Wolf* e) = 0;
	virtual void visit(Sheep* e) = 0;
	virtual void visit(Grass* e) = 0;
};

#endif
