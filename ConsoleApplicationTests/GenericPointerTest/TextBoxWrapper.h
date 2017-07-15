#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

namespace ui
{
	using namespace std;
	using namespace nana;
	
	using boost::lexical_cast;
	using boost::bad_lexical_cast;
	
	template<class T>
	class TextBoxWrapper
	{
	public:
		textbox tbx_;	// (fm, rectangle{ 20, 20, 150, 30 });
		label lab_;
		T &var_;		// reference to the variable that should be updated when text_ is edited

		TextBoxWrapper(const form& _fm, const rectangle& _rect_label, const rectangle& _rect_textbox, const string& label_str, T& _var)
			: lab_(_fm, _rect_label), tbx_(_fm, _rect_textbox), var_(_var)
		{
			lab_.caption(label_str);
			lab_.text_align(align::left, align_v::center);
			
			tbx_.multi_lines(false);
			tbx_.caption(lexical_cast<string>(var_));	// default value
			tbx_.events().text_changed([&](const nana::arg_textbox& a_b) {
				string text;
				a_b.widget.getline(0, text);
				str_to_value(text, var_);
			});
		}

		~TextBoxWrapper()
		{
			cout << "destructor" << endl;
		}

		template<class T>
		void str_to_value(const string& str, T& v)
		{
			T backup = v;
			try { v = lexical_cast<T>(str); }
			catch (const bad_lexical_cast &) { v = backup; } // roll back
		}
	};

}