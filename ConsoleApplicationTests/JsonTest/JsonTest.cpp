// JsonTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "nlohmann\json.hpp"

int main()
{
	using namespace nlohmann;
	using namespace std;

	json vars;

	// make json
	{
		json v0;
		v0["name"] = "name1";
		v0["type"] = "type1";

		json v1;
		v1["name"] = "name2";
		v1["type"] = "type2";

		vector<json> vv;
		vv.push_back(v0);
		vv.push_back(v1);

		vars["category"] = "Test parameters";
		vars["variables"] = vv;
	}

	cout << vars << endl;

	// read from json
	{
		const string category_name = vars["category"].get<string>();

		cout << category_name << endl;

		const vector<json> vv = vars["variables"].get<vector<json>>();

		for (auto &itr : vv)
		{
			// itr is json type
			cout << itr["name"].get<string>() << " " << itr["type"].get<string>() << endl;
		}
	}
	


    return 0;
}

