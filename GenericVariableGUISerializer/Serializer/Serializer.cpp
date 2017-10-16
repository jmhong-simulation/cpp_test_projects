#include "Serializer.h"
#include <string>

using namespace std;

namespace serializer
{
	template<class TT>
	void Serializer::add(const string & _name, TT & _var)
	{
		getTab(current_tab)->getGroup(current_group)->variables_.push_back(new GenericVariable<TT>(_name, _var));
	}

	// template specialization (not to include string)
	template void Serializer::add(const string& _name, bool& _var);
	template void Serializer::add(const string& _name, int& _var);
}



