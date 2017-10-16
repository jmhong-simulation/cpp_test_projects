#pragma once

#include <string>

namespace serializer {

	using namespace std;

	class GenericVariableBase
	{
	public:
		string name;
	};

	typedef GenericVariableBase BASE;

	template<class TT>
	class GenericVariable : public GenericVariableBase
	{
	public:
		TT& variable;

		using BASE::name;

		GenericVariable(const string& _name, TT& _var)
			: variable(_var)
		{
			name = _name;
		}
	};

}//end of namespace serializer