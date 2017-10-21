#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "EventHandler.h"

namespace jm
{
	using namespace std;

	class EventManager
	{
	public:

		vector<EventHandlerBase*> event_handlers;

		EventManager()
		{
		}

		~EventManager()
		{
		}

		void addNew(EventHandlerBase* new_event)
		{

		}
	};
}
