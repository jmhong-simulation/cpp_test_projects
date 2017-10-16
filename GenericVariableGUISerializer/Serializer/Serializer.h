#pragma once

#include <vector>
#include <map>

#include "GenericVariable.h"

namespace serializer{

	using namespace std;

	class Serializer
	{
	public:
		string current_tab;
		string current_group;

		class Group
		{
		public:
			vector<GenericVariableBase*> variables_;

			~Group()
			{
				for (int i = 0; i < variables_.size(); ++i)
				{
					delete variables_[i];
					variables_[i] = nullptr;
				}
			}
		};

		class Tab
		{
		public:
			map<string, Group*> groups_;

			Group* getGroup(const string& _name)
			{
				if (groups_.count(_name) == 0) groups_[_name] = new Group;

				return groups_[_name];
			}
		};

		map<string, Tab*> tabs_;

		Serializer()
		{
			current_tab = string("default");
			current_group = string("default");
		}

		Tab* getTab(const string& _name)
		{
			if (tabs_.count(_name) == 0) tabs_[_name] = new Tab;

			return tabs_[_name];
		}

		template<class TT> void add(const string& _name, TT& _var);
	};



} // end of namespace serializer