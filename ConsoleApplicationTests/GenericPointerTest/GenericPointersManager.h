#pragma once

#include <vector>
#include "GenericPointer.h"

namespace binding
{
	using namespace nlohmann;

	class GenericPointersManager
	{
	private:
		string name_;

		vector<GenericPointer*> ptrs_;

	public:
		GenericPointersManager(const string& _name)
			: name_(_name)
		{
		}

		~GenericPointersManager()
		{
			for (auto &itr : ptrs_) delete itr;
		}

		void addNew(GenericPointer* gp)
		{
			ptrs_.push_back(gp);
		}

		template<class T>
		void addNew(const string& _var_name, T& _var)
		{
			addNew(new GenericPointer(_var_name, _var));
		}

		json getJson()
		{
			json js;

			vector<json> var_vec;

			for (auto &itr : ptrs_)
			{
				json var_js = itr->getJson();

				var_vec.push_back(var_js);

				// retrieve test -> OK!
				/*{
					string str = var_js["address"].get<string>();
					int* ptr = (int*)GenericPointer::address_string_to_void_ptr(str);
					cout << *ptr << endl;

					exit(1);
				}*/
			}

			js["category"] = this->name_;
			js["variables"] = var_vec;

			// retrieve test -> OK!
			//{
			//	const json js2 = js;

			//	vector<json> js_temp = js2["variables"];
			//	json js_var = js_temp[0].get<json>(); // do not skip this step!

			//	string str = js_var["address"].get<string>();

			//	int* ptr = (int*)GenericPointer::address_string_to_void_ptr(str);

			//	cout << "Retrieve test " << *ptr << endl;

			//	exit(1);
			//}

			return js;
		}
	};
}
