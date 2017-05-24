#ifndef INFOSV_INFECTER
#define INFOSV_INFECTER
#include <Interface/Visitor.hpp>

/*!
 * @class Infecter
 *
 * @brief Visitor used to spread the infection among the
  		  animals it visits.
 */
class Infecter: public Visitor {
public:
	/*!
	 * @brief Creates new Infection Spreader
	 *
	 * @param v The virus to spread
	 */
	Infecter(Virus* v);
	void visit(Wolf* e);
	void visit(Sheep* e);
	void visit(Grass* e);
private:
	Virus* virus;
};

#endif;