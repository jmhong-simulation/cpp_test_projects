// GenericPointerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GenericPointer.h"
#include "GenericWidget.h"

using namespace binding;

template<class T>
void test_function()
{
	T temp = (T)123.456;

	cout << temp << endl;
}

template<typename T> void(*ptr_func)();

int main()
{
	ptr_func<int> = &test_function<int>;

	(*ptr_func<int>)();

	int int_var = 1024;

	cout << int_var << endl;

	GenericPointer p1("int_var", int_var);

	p1.getRef<int>() = 2048;

	cout << int_var << endl;

	json js = p1.getJson();

	cout << js << endl;

	GenericPointer p2(js);

	p2.getRef<int>() = 512;

	cout << int_var << endl;

	ui::GenericWidget test_widget("Parameters");

    return 0;
}

