#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#pragma once

#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <string>
#include <iostream>

class TestGUI
{
public:
	TestGUI()
	{
		using namespace std;
		using namespace nana;

		form fm;
		fm.caption("Hello, Nana Window!");

		button btn(fm, rectangle{ 20, 50, 100, 30 });
		btn.caption("Print Something");
		//btn.events().click(API::exit);
		btn.events().click([]() {cout << "GUI Button Click" << endl; });

		fm.show();
		exec();
	}
};
