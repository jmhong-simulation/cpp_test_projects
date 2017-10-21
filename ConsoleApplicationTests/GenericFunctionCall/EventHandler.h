#pragma once

#include <functional>

namespace jm
{
	using namespace std;

	class EventHandlerBase
	{
	public:
		//virtual void invoke() = 0;
	};

	template<class T_CLASS, class T_FUNCTION>
	class EventHandler : public EventHandlerBase
	{
	public:
		T_CLASS *class_ptr = nullptr;
		T_FUNCTION func;

		EventHandler(T_FUNCTION _func)
			: func(_func)
		{}

		~EventHandler()
		{}

		template<class ... Args>
		void invoke(Args ... args)
		{
			(class_ptr->*func)(args ...);
		}
	};
}
