#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <string>
#include <vector>
#include "TextBoxWrapper.h"
#include "Serializer.h"

namespace serializer
{
	using namespace nana;
	using namespace std;

	class ParametersControlForm
	{
	private:
		form fm;

		vector<WidgetBase*> widgets_;

	public:
		ParametersControlForm(const string& title)
		{
			fm.caption(title);
		}

		~ParametersControlForm()
		{
			//cout << __FUNCTION__ << endl;

			freeWidgets();
		}

		void resize_and_move_to_center(const nana::size& new_size)
		{
			nana::size screen_size(screen::primary_monitor_size());
			nana::size form_size(new_size);		// determine by number of inputs

			fm.size(form_size);
			fm.move((screen_size.width - form_size.width) / 2, (screen_size.height - form_size.height) / 2);
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

		void addVariables(Serializer& serializer)
		{
			for (auto& tab_itr : serializer.tabs_)
			{
				for (auto& group_itr : tab_itr.second->groups_)
				{
					for (auto& var_itr : group_itr.second->variables_)
					{
						cout << var_itr->name << endl;
					}
				}
			}
		}

		//void addVariablesGroup(const json& vars_js)
		//{			
		//	const string category_name = vars_js["category"].get<string>();
		//	const vector<json> jsvars_vec = vars_js["variables"].get<vector<json>>();

		//	const int compt_height = 20;
		//	const int com0_width = 50;
		//	const int com1_width = 150;
		//	const int com2_width = 100;
		//	const int com3_width = 100;
		//	const int h_border = 10;
		//	const int w_border = 10;
		//	const int l_border = 10; // left border from window

		//	for(int count = 0; count < jsvars_vec.size(); ++count)
		//	{
		//		const json var_js = jsvars_vec[count].get<json>();		// do not skip this step (do not use itr of jsvars_vec)

		//		const string name = var_js["name"].get<string>();
		//		const string type = var_js["type"].get<string>();
		//		const string ptr_str = var_js["address"].get<string>();

		//		int x_pos = l_border;
		//		const rectangle type_rect = rectangle{ x_pos, h_border + count * (compt_height + h_border), (unsigned)com0_width, (unsigned)compt_height };
		//		x_pos += com0_width + w_border;
		//		const rectangle label_rect = rectangle{ x_pos, h_border + count * (compt_height + h_border), (unsigned)com1_width, (unsigned)compt_height };
		//		x_pos += com1_width + w_border;
		//		const rectangle txt_rect = rectangle{ x_pos, h_border + count * (compt_height + h_border), (unsigned)com2_width, (unsigned)compt_height };
		//		x_pos += com2_width + w_border;
		//		const rectangle value_rect = rectangle{ x_pos, h_border + count * (compt_height + h_border), (unsigned)com3_width, (unsigned)compt_height };

		//		WidgetBase *new_widget = getNewTextBoxWrapper(name, type, ptr_str, fm, type_rect, label_rect, txt_rect, value_rect);

		//		widgets_.push_back(new_widget);
		//	}
		//	
		//	const int total_width = l_border + com0_width + w_border + com1_width + w_border + com2_width + w_border + com3_width + l_border;
		//	const int total_height = h_border + (compt_height + h_border)* jsvars_vec.size() + h_border;

		//	resize_and_move_to_center(nana::size(total_width, total_height));
		//}

		void show_and_exec()
		{
			fm.show();
			nana::exec();
		}
	};

}