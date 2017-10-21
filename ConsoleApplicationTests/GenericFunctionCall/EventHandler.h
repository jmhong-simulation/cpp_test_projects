#pragma once

#include <functional>
#include <string>
#include <iostream>
#include <assert.h>

namespace jm
{

#define FATAL_ERROR(message) {cout << __FUNCTION__ <<" : "<< message << endl; assert(false); system("pause"); exit(1);}

	using namespace std;

	class EventHandlerBase
	{
	public:
		virtual void update(const bool& _value)   { FATAL_ERROR("Wrong bool"); };
		virtual void update(const double& _value) { FATAL_ERROR("Wrong double"); };
		virtual void update(const float& _value)  { FATAL_ERROR("Wrong float"); };
		virtual void update(const int& _value)    { FATAL_ERROR("Wrong int"); };
		virtual void update(const string& _value) { FATAL_ERROR("Wrong string"); };

		virtual void invoke() = 0;
		virtual string getTypeNameStr() = 0;
	};

	template<typename T_FUNCTION>
	class EventHandler : public EventHandlerBase
	{
	public:
		T_FUNCTION func;

		EventHandler(T_FUNCTION& _func)
			: func(_func)
		{}

		~EventHandler()
		{}

		void invoke()
		{
			func();
		}

		string getTypeNameStr()
		{
			return string(typeid(func).name());
		}
	};

	template<typename ... Args>
	auto makeNewEventHandler(Args ... args)
	{
		auto bnd = bind(args ...);
		auto *new_event_handler = new EventHandler<decltype(bnd)>(bnd);

		return new_event_handler;
	}

	template<typename T_TYPE>
	class VariableConnector : public EventHandlerBase
	{
	public:
		T_TYPE value_buffer;
		T_TYPE &variable_ref;

		VariableConnector(T_TYPE& _var_ref)
			: variable_ref(_var_ref)
		{}

		void update(const T_TYPE& _value)
		{
			value_buffer = _value;
		}

		void invoke()
		{
			variable_ref = value_buffer;
		}

		string getTypeNameStr()
		{
			return string(typeid(variable_ref).name());
		}
	};
}
