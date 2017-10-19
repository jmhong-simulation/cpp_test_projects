#pragma once

#include <iostream>

class TestClass1
{
public:
	TestClass1()
	{
	}

	~TestClass1()
	{
	}

	void printName()
	{
		using namespace std;

		cout << typeid(*this).name() << endl;
	}
};
