#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "EventHandler.h"

namespace jm
{

	using namespace std;

	class ButtonConnector
	{
	public:
		EventHandlerBase *event_handler = nullptr;
	};

	class TextEditConnector
	{
	public:
		EventHandlerBase *event_handler = nullptr;
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
