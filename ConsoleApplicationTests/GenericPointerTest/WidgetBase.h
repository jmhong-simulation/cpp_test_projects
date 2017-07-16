#pragma once

#include <string>

namespace ui
{
	using namespace std;

	class WidgetBase
	{
	public:

		virtual ~WidgetBase() // virtual destructor is necessary to cleanup child classes under polymorphysm
		{
			cout << __FUNCTION__ << endl;
		}

		template<class T>
		static bool isType(const string& type)
		{
			if (typeid(T).name() == type) return true;
			else return false;
		}

		static void* address_string_to_void_ptr(const string& add_str)
		{
			void *void_ptr_back;
			sprintf((char*)&void_ptr_back, add_str.c_str());

			return void_ptr_back;
		}
	};
}