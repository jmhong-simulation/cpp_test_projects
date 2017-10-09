#include <iostream>

class OuterClass
{
public:
	class InnerClass
	{
	public:
		int a_ = 123;
	};

	InnerClass data, data2;
};

int main()
{
	OuterClass oc;

	oc.data.a_ = 456;
	oc.data2.a_ = 657;

	return 0;
}