#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "WidgetBase.h"

namespace serializer
{

#define FATAL_ERROR(message) {cout << __FUNCTION__ << endl; cout << message << endl; assert(false); exit(1);}

	using namespace std;
	using namespace nana;
	
	using boost::lexical_cast;
	using boost::bad_lexical_cast;
	
	template<class T>
	class TextBoxWrapper : public WidgetBase
	{
	public:
		label	type_label_;
		textbox name_label_;
		textbox input_tbx_;
		label	value_label_;

		T &var_;		// reference to the variable that should be updated when text_ is edited //TODO: store variable and use sync!

		TextBoxWrapper(const form& _fm, const rectangle& _rect_type, const rectangle& _rect_label, const rectangle& _rect_textbox, 
					  const rectangle& _rect_value, const string& name_str, T& _var)
			: type_label_(_fm, _rect_type), name_label_(_fm, _rect_label), input_tbx_(_fm, _rect_textbox), value_label_(_fm, _rect_value), var_(_var)
		{
			type_label_.caption(getShortTypeName<T>());
			type_label_.text_align(align::right);
			/*type_label_.fgcolor(nana::colors::black);*/
			
			//type_label_.bgcolor(nana::colors::white_smoke);

			name_label_.caption(name_str);
			name_label_.text_align(align::center);
			name_label_.fgcolor(nana::colors::black);
			name_label_.bgcolor(nana::colors::papaya_whip);
			name_label_.editable(false);
			name_label_.enabled(false);
			name_label_.select(false);

			input_tbx_.multi_lines(false);
			input_tbx_.caption(lexical_cast<string>(var_));	// default value
			/*input_tbx_.events().text_changed([&](const nana::arg_textbox& a_b) {
				string text;
				a_b.widget.getline(0, text);
				str_to_value(text, var_);

				value_label_.caption(lexical_cast<string>(var_));
			});*/

			// Enter apply changes, ESC undo
			input_tbx_.events().key_release([&](const nana::arg_keyboard& ak) {
				if (ak.key == 13)    // 'Enter' apply changes
				{
					string text;
					input_tbx_.getline(0, text);

					if (str_to_value(text, var_))
					{
						value_label_.caption(lexical_cast<string>(var_));
					}
				}
				else if(ak.key == 27)	// 'ESC' undo changes
				{
					input_tbx_.caption(lexical_cast<string>(var_));

					//TODO: move cursor to the last of text
				}
			});

			// Double click selects all text
			input_tbx_.events().dbl_click([&](const nana::arg_mouse& am) {
				input_tbx_.select(true);
			});

			value_label_.caption(lexical_cast<string>(var_));
			value_label_.text_align(align::left, align_v::center);
		}

		~TextBoxWrapper()
		{
			//cout << "destructor" << endl;
		}

		template<class T>
		bool str_to_value(const string& str, T& v)
		{
			T backup = v;

			try 
			{
				v = lexical_cast<T>(str); 
			}
			catch (const bad_lexical_cast &)
			{
				v = backup; 

				return false; 
			} // roll back

			return true;
		}

		template<class T>
		string getShortTypeName()
		{
			if (typeid(T).name() == typeid(int).name()) return "int";
			else if (typeid(T).name() == typeid(float).name()) return "float";
			else if (typeid(T).name() == typeid(double).name()) return "double";
			else if (typeid(T).name() == typeid(bool).name()) return "bool";
			else if (typeid(T).name() == typeid(string).name()) return "string";
			else FATAL_ERROR("Not defined type name " << typeid(T).name());
		}
	};

	// factory
	static WidgetBase* getNewTextBoxWrapper(const string& name, const string& type, const string& ptr_str, const form& fm, 
											const rectangle& _rect_type, const rectangle& _rect_label, const rectangle& _rect_textbox, const rectangle& _value_label)
	{
		if (WidgetBase::isType<int>(type))
		{
			int *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<int>(fm, _rect_type, _rect_label, _rect_textbox, _value_label, name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<float>(type))
		{
			float *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<float>(fm, _rect_type, _rect_label, _rect_textbox, _value_label, name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<double>(type))
		{
			double *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<double>(fm, _rect_type, _rect_label, _rect_textbox, _value_label, name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<bool>(type))
		{
			bool *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<bool>(fm, _rect_type, _rect_label, _rect_textbox, _value_label, name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<string>(type))
		{
			string *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<string>(fm, _rect_type, _rect_label, _rect_textbox, _value_label, name, *ptr);

			return new_widget;
		}
		else
		{
			FATAL_ERROR("Operation for this type is not defined " << type);
		}
	}

}