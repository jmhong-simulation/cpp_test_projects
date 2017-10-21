#pragma once

#include <functional>

namespace jm
{
	using namespace std;

	class EventHandlerBase
	{
	public:
		virtual void invoke() = 0;


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
	};

	template<typename ... Args>
	auto makeNewEventHandler(Args ... args)
	{
		auto bnd = bind(args ...);
		auto *new_event_handler = new EventHandler<decltype(bnd)>(bnd);

		return new_event_handler;
	}
}
