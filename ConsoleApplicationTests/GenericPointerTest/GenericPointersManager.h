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
			}

			js["category"] = this->name_;
			js["variables"] = var_vec;

			return js;
		}
	};
}
