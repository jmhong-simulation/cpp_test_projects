#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "EventHandler.h"

namespace jm
{

	using namespace std;

	class GUIElementBase
	{
	public:
		string tab_name;
		string group_name;
		string label_name;

		enum Type { Button, TextEdit, TwoButtons } type;

		EventHandlerBase *event_handler = nullptr;

		GUIElementBase()
		{
		}
	};

	class TextEditElement : public GUIElementBase
	{
	public:
		TextEditElement()
		{
			type = Type::TextEdit;
		}
	};

	class ButtonElement : public GUIElementBase
	{
	public:
		ButtonElement()
		{
			type = Type::Button;
		}
	};

	class TwoButtonsElement : public GUIElementBase
	{
	public:
		string label_name2;
		EventHandlerBase *event_handler_2 = nullptr;

		TwoButtonsElement()
		{
			type = Type::TwoButtons;
		}
	};

	class GUIConnector
	{
	public:

		vector<GUIElementBase*> gui_elements;

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
