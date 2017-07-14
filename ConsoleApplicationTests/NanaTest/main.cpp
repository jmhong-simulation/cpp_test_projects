#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>

#include <iostream>

using namespace std;
using namespace nana;

class TextBoxWrapper
{
public:
	textbox tbx_;	// (fm, rectangle{ 20, 20, 150, 30 });
	string text_;	// text buffer
	label lab_;

	TextBoxWrapper(const form& _fm, const rectangle& _rect_label, const rectangle& _rect_textbox)
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

int main()
{
	

	form fm;
	fm.caption(L"Hello, World!");

	TextBoxWrapper tbx(fm, rectangle{ 20, 20, 60, 20 }, rectangle{ 100, 20, 150, 20 });

	//textbox tbx(fm, rectangle{ 20, 20, 150, 30 });
	//tbx.caption("Hello, Textbox");
	///*tbx.set_highlight("sqlrev", colors::dark_blue, colors::yellow);
	//tbx.set_keywords("sqlrev", false, true, { "select", "from", "where" });*/
	//tbx.multi_lines(false);
	//tbx.events().key_release(foo);


	// add a button
	button btn(fm, rectangle{ 20, 50, 150, 30 });
	btn.caption(L"Quit");
	btn.events().click(API::exit);

	fm.show();
	exec();
}