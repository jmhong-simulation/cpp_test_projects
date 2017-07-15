#pragma once

#include "GenericPointer.h"
#include <vector>

namespace binding
{
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
	};
}
