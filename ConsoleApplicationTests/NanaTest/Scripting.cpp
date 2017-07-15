#include "Scripting.h"

using namespace scripting;

scripting::Category::Category(const string & _name)
	: name_(_name)
{}

scripting::Category::~Category()
{
	for (const auto& itr : vars_vec_)	delete itr;
}
