#include <iostream>

#include "TemplatizedClass.h"
#include "TestClass1.h"
#include "TestClass2.h"

int main()
{

	TemplatizedClass<TestClass1> tc1;
	tc1.work();

	//TemplatizedClass<TestClass2> tc2;
	//tc2.work();						// compiles ok if this line is commented

	return 0;
}

//template class TemplatizedClass<TestClass2>; // generates build error (good for debugging!)