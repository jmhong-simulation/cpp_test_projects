#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "WidgetBase.h"

namespace ui
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
		textbox tbx_;	// (fm, rectangle{ 20, 20, 150, 30 });
		label lab_;
		T &var_;		// reference to the variable that should be updated when text_ is edited

		TextBoxWrapper(const form& _fm, const rectangle& _rect_label, const rectangle& _rect_textbox, const string& label_str, T& _var)
			: lab_(_fm, _rect_label), tbx_(_fm, _rect_textbox), var_(_var)
		{

			//cout << var_ << endl;

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

	// factory
	static WidgetBase* getNewTextBoxWrapper(const string& name, const string& type, const string& ptr_str, const form& fm, const rectangle& _rect_label, const rectangle& _rect_textbox)
	{
		/*cout << __FUNCTION__ << endl;

		int* ptr = (int*)WidgetBase::address_string_to_void_ptr(ptr_str);
		cout << "Retrieve test " << __FUNCTION__ << endl << *ptr << endl;*/
		//exit(1);

		if (WidgetBase::isType<int>(type))
		{
			int *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<int>(fm, _rect_label, _rect_textbox, string("int ") + name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<float>(type))
		{
			float *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<float>(fm, _rect_label, _rect_textbox, string("float ") + name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<double>(type))
		{
			double *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<double>(fm, _rect_label, _rect_textbox, string("double ") + name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<bool>(type))
		{
			bool *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<bool>(fm, _rect_label, _rect_textbox, string("bool ") + name, *ptr);

			return new_widget;
		}
		else if (WidgetBase::isType<string>(type))
		{
			string *ptr = nullptr;		// these took 1 hour debugging. string to ptr
			sprintf((char*)&ptr, ptr_str.c_str());

			WidgetBase *new_widget = new TextBoxWrapper<string>(fm, _rect_label, _rect_textbox, string("string ") + name, *ptr);

			return new_widget;
		}
		else
		{
			FATAL_ERROR("Operation for this type is not defined " << type);
		}
	}

}