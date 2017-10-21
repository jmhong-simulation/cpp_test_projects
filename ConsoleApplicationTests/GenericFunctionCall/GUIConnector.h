#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

namespace jm
{

#define FATAL_ERROR {cout << __FUNCTION__ << endl; assert(false); system("pause"); exit(1);}

	using namespace std;

	class ButtonConnectorBase
	{
	public:
		virtual void invoke() = 0;
	};

	class TextEditConnectorBase
	{
	public:
		virtual void update(const int& _value) { FATAL_ERROR };
		virtual void update(const string& _value) { FATAL_ERROR };
		virtual void update(const float& _value) { FATAL_ERROR };
		virtual void update(const bool& _value) { FATAL_ERROR };
		virtual void update(const double& _value) { FATAL_ERROR };

		virtual void invoke() = 0;
	};

	template<typename T_TYPE>
	class TextEditConnector : public TextEditConnectorBase
	{
	public:
		T_TYPE value_buffer;
		T_TYPE &variable_ref;

		TextEditConnector(T_TYPE& _var_ref)
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
	};

	class GUIConnector
	{
	public:
		GUIConnector()
		{
		}

		~GUIConnector()
		{
		}

		template<class T_TYPE>
		void registerTextEdit(const string& name, T_TYPE& variable)
		{
		}

		template<class T_FUNC>
		void registerButton(const string& name, T_FUNC& func)
		{
		}
	};
}
