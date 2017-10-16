#pragma once

#include <string>

namespace serializer {

	using namespace std;

	class GenericVariableBase
	{
	public:
		string name;
		string type_name;

		virtual string getStrAddress() = 0;

		static string void_ptr_to_address_string(void *void_ptr)
		{
			string address_str;
			address_str.resize(sizeof(void*));			// x64: 8, x86: 4
			sprintf(&address_str[0], (char*)&void_ptr);

			return address_str;
		}
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
			type_name = typeid(TT).name();
		}

		string getStrAddress()
		{
			return BASE::void_ptr_to_address_string((void*)&variable);
		}
	};
}//end of namespace serializer