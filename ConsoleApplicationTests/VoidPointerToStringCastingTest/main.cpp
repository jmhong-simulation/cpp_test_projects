// VoidPointerToStringCastingTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int variable = 1024;				// target variable
	void *ptr_var = (void*)&variable;	// cast to void pointer

	cout << ptr_var << endl;

	// save void pointer as string
	string ptr_str;
	ptr_str.resize(sizeof(void*));
	sprintf(&ptr_str[0], (char*)&ptr_var);

	cout << ptr_str << endl;

	// ... copying, sending pointer to somewhere else.

	// restore void pointer from string
	void *ptr_back;
	sprintf((char*)&ptr_back, ptr_str.c_str());

	cout << ptr_back << endl;

	// cast void pointer to int pointer again
	int *int_ptr_back = (int*)ptr_back;
	*int_ptr_back = 2048;

	cout << variable << endl;

    return 0;
}

