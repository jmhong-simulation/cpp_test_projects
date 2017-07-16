#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <string>
#include <vector>
#include "nlohmann\json.hpp"
#include "TextBoxWrapper.h"

namespace ui
{
	using namespace nana;
	using namespace std;
	using namespace nlohmann;

	class ParametersControlForm
	{
	private:
		form fm;

		vector<WidgetBase*> widgets_;

	public:
		ParametersControlForm(const string& title)
		{
			fm.caption(title);

			nana::size screen_size(screen::primary_monitor_size());
			nana::size form_size(800, 1000);		// determine by number of inputs

			fm.size(form_size);
			fm.move((screen_size.width - form_size.width)/2, (screen_size.height - form_size.height) / 2);

			int test_int = 1234;
			//float test_f = 3.14;
			//string test_str = "Hello, JM";
			//bool  test_bool = true;

			////TODO: use polymorphism
			////TODO: use json to automatically initialize these
			//TextBoxWrapper<int> tbx(fm, rectangle{ 20, 30, 60, 20 }, rectangle{ 100, 30, 100, 20 }, "int test_int", test_int);
			//TextBoxWrapper<float> tbx2(fm, rectangle{ 20, 50, 60, 20 }, rectangle{ 100, 41, 100, 20 }, "float test_f", test_f);
			//TextBoxWrapper<string> tbx3(fm, rectangle{ 20, 75, 60, 20 }, rectangle{ 100, 62, 100, 20 }, "string test_str", test_str);
			//TextBoxWrapper<bool> tbx4(fm, rectangle{ 20, 100, 60, 20 }, rectangle{ 100, 83, 100, 20 }, "bool test_bool", test_bool);

			//cout << test_int << endl;
			//cout << test_f << endl;
			//cout << test_str << endl;
			//cout << test_bool << endl;
		}

		~ParametersControlForm()
		{
			cout << __FUNCTION__ << endl;

			freeWidgets();
		}

		void freeWidgets()
		{
			//for (auto &itr : widgets_) delete itr;
			for (int i = 0; i < widgets_.size(); ++i)
			{
				delete widgets_[i];
			}

			widgets_.clear();
		}

		void addVariablesGroup(const json& vars_js)
		{
			//{
			//	const json js2 = vars_js;

			//	const vector<json> js_temp = js2["variables"];
			//	const json js_var = js_temp[0].get<json>(); // do not skip this step!

			//	const string str = js_var["address"].get<string>();

			//	int* ptr = (int*)WidgetBase::address_string_to_void_ptr(str);

			//	cout << "Retrieve test " << __FUNCTION__ << endl << *ptr << endl;

			//	exit(1);
			//}

			const string category_name = vars_js["category"].get<string>();
			const vector<json> jsvars_vec = vars_js["variables"].get<vector<json>>();
			//const vector<json> jsvars_vec = vars_js["variables"];

			/*{
				const json js_var = jsvars_vec[0].get<json>();
				const string str = js_var["address"].get<string>();
				cout << "size of str " << str.size() << endl;
				int* ptr = (int*)WidgetBase::address_string_to_void_ptr(str);
				cout << "Retrieve test " << __FUNCTION__ << endl << *ptr << endl;
				exit(1);
			}*/

			/*cout << "Category name " << category_name << endl;
			cout << jsvars_vec.size() << endl;*/


			int count = 0;
			for(int i = 0; i < jsvars_vec.size(); ++i)
			{
				const json var_js = jsvars_vec[i].get<json>();		// do not skip this step (do not use itr of jsvars_vec)

				const string name = var_js["name"].get<string>();
				const string type = var_js["type"].get<string>();
				const string ptr_str = var_js["address"].get<string>();

				/*int* ptr = (int*)WidgetBase::address_string_to_void_ptr(ptr_str);
				cout << "Retrieve test " << __FUNCTION__ << endl << *ptr << endl;
				exit(1);*/

				const rectangle label_rect = rectangle{ 20, count * 30 + 20, 60, 20 };
				const rectangle txt_rect = rectangle{ 100, count * 30 + 20, 100, 20 };

				WidgetBase *new_widget = getNewTextBoxWrapper(name, type, ptr_str, fm, label_rect, txt_rect);
				widgets_.push_back(new_widget);

				count++;
			}
		}

		void show_and_exec()
		{
			fm.show();
			nana::exec();
			freeWidgets();
		}
	};

}