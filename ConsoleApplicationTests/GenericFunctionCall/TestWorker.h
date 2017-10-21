#pragma once

#include <string>
#include <iostream>
#include "EventManager.h"
#include "EventHandler.h"

using namespace std;
using namespace jm;

class TestWorker
{
public:
	bool is_continue = true;

	int count = 0;

	EventManager event_manager;

	template<class T_OWNER, class T_FUNC_PTR>
	auto makeEventHandler(T_OWNER *owner_ptr, T_FUNC_PTR func_ptr)
	{
		auto new_handler = new EventHandler<TestWorker, decltype(func_ptr)>
								(
									func_ptr
								);

		new_handler->class_ptr = this;

		return new_handler;
	}

	TestWorker()
	{
		// register 'event' to event handler
		//event_manager.registerHandler("print", &TestWorker::print, this);
		/*auto func = function<void(const string&)>([this](const string& input_string) {this->print(input_string);});
		auto* new_handler = new EventHandler<function<void(const string&)>>(func);*/

		/*auto* new_handler = new EventHandler<TestWorker, void(TestWorker::*)(const string&), const string>
			(
				&TestWorker::print
			);*/

		auto* new_handler = makeEventHandler(this, &TestWorker::print);

		new_handler->invoke(string("Hello print"));
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
};