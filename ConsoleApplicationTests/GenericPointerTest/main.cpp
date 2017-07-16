// GenericPointerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GenericPointersManager.h"
#include "ParametersControlForm.h"

int main()
{
	using namespace binding;

	int    x_res = 64;
	float  PI = 3.141592;
	bool   train_new = true;

	GenericPointersManager vars("Autoencoder Parameters");

	vars.addNew("x_res", x_res);
	vars.addNew("PI", PI);
	vars.addNew("train_new", train_new);

	json vars_js = vars.getJson();

	ui::ParametersControlForm test_widget("Parameter Control Window");

	test_widget.addVariablesGroup(vars_js);
	test_widget.show_and_exec();

	cout << x_res << endl;
	cout << PI << endl;
	cout << train_new << endl;

    return 0;
}

