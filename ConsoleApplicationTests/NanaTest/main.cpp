#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/tabbar.hpp>

#include "Scripting.h"

#include <iostream>

using namespace std;
using namespace nana;

class TextBoxWrapper
{
public:
	textbox tbx_;	// (fm, rectangle{ 20, 20, 150, 30 });
	string text_;	// text buffer
	label lab_;

	TextBoxWrapper(nana::window _fm, const rectangle& _rect_label, const rectangle& _rect_textbox)
		: lab_(_fm, _rect_label), tbx_(_fm, _rect_textbox)
	{
		lab_.caption("int res_x");
		lab_.text_align(align::left, align_v::center);

		tbx_.multi_lines(false);
		tbx_.caption("Hello, Textbox");
		tbx_.events().key_release([&](const nana::arg_keyboard& a_k) {
			if (a_k.key == 13) {
				cout << "Enter Key pressed " << endl;
				cout << this->text_ << endl;
			}
		});

		tbx_.events().text_changed([&](const nana::arg_textbox& a_b) {
			string text_line;
			a_b.widget.getline(0, text_line);
			text_ = text_line;
		});

		tbx_.getline(0, text_);

		cout << text_ << endl;
	}

	void foo(const nana::arg_keyboard& a_k)
	{
		if (a_k.key == 13)
		{
			cout << "Enter Key pressed " << endl;
		}
	}

};

using namespace nlohmann;
using namespace scripting;

int main()
{
	json j, j2;
	
	j["type"] = "int";
	j["name"] = "x_res";
	j["value"] = "256";

	j2["variable"] = j;
	j2["variable2"] = j;

	// special iterator member functions for objects
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		//std::cout << it.key() << " : " << it.value() << "\n";
		cout << it.value().get<string>() << endl;
	}

	int test_int = 1;
	float test_float = 2.0;
	bool test_bool = false;
	string test_str = "Hello, test string";
	Category test_params("test_parameters");
	test_params.addNew("test_int", test_int);
	test_params.addNew("test_float", test_float);
	test_params.addNew("test_bool", test_bool);
	test_params.addNew("test_str", test_str);

	test_params.getVariable<int>("test_int") = 1024;
	test_params.getVariable<float>("test_float") = 3.141592f;
	test_params.getVariable<bool>("test_bool") = true;
	test_params.getVariable<string>("test_str") = "This is string";

	test_params.dump();

	json params_json = test_params.getJson();

	cout << params_json << endl;

	cout << test_int << endl;

	// form
	form fm;
	fm.caption("Hello, Nana Window!");


	// group
	
	group grp(fm);
	grp.caption("Group Example");

	grp.move(rectangle{ 10, 50, 250, 100 });
	grp.div("vert margin=10 <>><>");
	TextBoxWrapper tbx(grp, rectangle{ 20, 20, 60, 20 }, rectangle{ 100, 20, 120, 20 }); // use nana:window type 

	//textbox tbx(fm, rectangle{ 20, 20, 150, 30 });
	//tbx.caption("Hello, Textbox");
	///*tbx.set_highlight("sqlrev", colors::dark_blue, colors::yellow);
	//tbx.set_keywords("sqlrev", false, true, { "select", "from", "where" });*/
	//tbx.multi_lines(false);
	//tbx.events().key_release(foo);

	// add a button
	button btn(grp, rectangle{ 20, 50, 50, 30 });
	btn.caption(L"Quit");
	btn.events().click(API::exit);

	// tab bars
	tabbar<string> tbar;
	tbar.create(fm);
	tbar.push_back(("Tab1"));
	tbar.push_back(("Tab2"));
	tbar.move(rectangle{ 5, 5, 250, 20 });
	tbar.attach(0, grp);
	tbar.activated(0);

	fm.show();
	exec();
}