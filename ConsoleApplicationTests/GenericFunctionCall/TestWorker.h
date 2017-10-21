#pragma once

#include <string>
#include <iostream>
#include "EventManager.h"
#include "EventHandler.h"
#include "GUIConnector.h"
#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;
using namespace jm;

class TestWorker
{
public:
	bool continue_flag = true;

	int count = 0;

	EventManager event_manager;

	GUIConnector gui;

	TestWorker()
	{
		//auto *new_event_handler = makeNewEventHandler(&TestWorker::changeContinueFlag, this);
		auto *new_event_handler = makeNewEventHandler([&]() {cout << "Hello Lambda " << this << endl; changeContinueFlag(); });
		new_event_handler->invoke();

		//TODO: event name, event time? "Button", "Continue/Pause"

		event_manager.addNew(new_event_handler);
	}

	void update()
	{
		cout << "Updating " << count << endl;
		count++;
	}

	void print(const string& str_to_print)
	{
		cout << "Worker prints : " << str_to_print << endl;
	}

	void print2(const string& str1, const string& str2)
	{
		cout << str1 << " " << str2 << endl;
	}

	void changeContinueFlag()
	{
		continue_flag = !continue_flag;

		cout << __FUNCTION__ << endl;
	}
};