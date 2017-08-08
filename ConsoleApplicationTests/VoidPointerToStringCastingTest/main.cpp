// VoidPointerToStringCastingTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

using namespace std;

void c_style_main();

class PointerStringConverter
{
public:
	template<class T>
	static std::string pointer_to_string(const T* variable)
	{
		// cast to void pointer
		void *ptr_var = (void*)variable;	

		// save void pointer as string
		string ptr_str;
		ptr_str.resize(sizeof(void*));
		sprintf(&ptr_str[0], (char*)&ptr_var);

		return ptr_str;
	}

	template<class T>
	static T* string_to_pointer(const string& ptr_str)
	{
		void *ptr_back = nullptr;
		sprintf((char*)&ptr_back, ptr_str.c_str());

		// cast void pointer to int pointer again
		return (T*)ptr_back;
	}
};

int main()
{
	c_style_main();

	// cpp style
	int test_variable = 768;
	const string ptr_str = PointerStringConverter::pointer_to_string(&test_variable);

	int *itr_ptr = PointerStringConverter::string_to_pointer<int>(ptr_str);

	cout << *itr_ptr << " should be equanl to " << test_variable << endl;

	*itr_ptr = 1024;

	cout << test_variable << " should be equanl to " << *itr_ptr << endl;

    return 0;
}

void c_style_main()
{
	// c style test

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
	void *ptr_back = nullptr;
	sprintf((char*)&ptr_back, ptr_str.c_str());

	cout << ptr_back << endl;

	// cast void pointer to int pointer again
	int *int_ptr_back = (int*)ptr_back;
	*int_ptr_back = 2048;

	cout << variable << endl;
}