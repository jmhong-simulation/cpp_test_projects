#pragma once

#include <iostream>
#include <string>

namespace jm
{
	using namespace std;

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
