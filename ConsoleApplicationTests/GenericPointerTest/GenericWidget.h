#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <string>
#include "nlohmann\json.hpp"
#include "TextBoxWrapper.h"

namespace ui
{
	using namespace nana;
	using namespace std;
	using namespace nlohmann;

	class GenericWidget
	{
	private:
		form fm;

	public:
		GenericWidget(const string& title)
		{
			fm.caption(title);

			nana::size screen_size(screen::primary_monitor_size());
			nana::size form_size(800, 1000);		// determine by number of inputs

			fm.size(form_size);
			fm.move((screen_size.width - form_size.width)/2, (screen_size.height - form_size.height) / 2);

			int test_int = 1234;
			float test_f = 3.14;
			string test_str = "Hello, JM";
			bool  test_bool = true;

			//TODO: use polymorphism
			//TODO: use json to automatically initialize these
			TextBoxWrapper<int> tbx(fm, rectangle{ 20, 25, 60, 20 }, rectangle{ 100, 20, 100, 20 }, "int test_int", test_int);
			TextBoxWrapper<float> tbx2(fm, rectangle{ 20, 50, 60, 20 }, rectangle{ 100, 41, 100, 20 }, "float test_f", test_f);
			TextBoxWrapper<string> tbx3(fm, rectangle{ 20, 75, 60, 20 }, rectangle{ 100, 62, 100, 20 }, "string test_str", test_str);
			TextBoxWrapper<bool> tbx4(fm, rectangle{ 20, 100, 60, 20 }, rectangle{ 100, 83, 100, 20 }, "bool test_bool", test_bool);

			fm.show();
			nana::exec();

			cout << test_int << endl;
			cout << test_f << endl;
			cout << test_str << endl;
			cout << test_bool << endl;
		}

		~GenericWidget()
		{
		}

	};

}