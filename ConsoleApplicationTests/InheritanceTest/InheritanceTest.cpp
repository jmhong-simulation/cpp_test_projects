// InheritanceTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Mother
{
	// member variables
public:
	int public_member_ = 1;
private:
	int private_member_ = 2;
protected:
	int protected_member_ = 3;

	// member functions
public:
	int& getPrivateMember()
	{
		return private_member_;
	}
};

class Child : public Mother
{
public:
	int public_member_ = 11;
	int private_member_ = 12;
	int protected_member_ = 13;

	void doSomething()
	{
		using namespace std;

		cout << Mother::public_member_ << endl;
		//cout << Mother::private_member_ << endl;  // cannot access private members directly in child
		cout << Mother::getPrivateMember() << endl; // cannot access directly in child
		cout << Mother::protected_member_ << endl;

		cout << Child::public_member_ << endl;
		cout << Child::private_member_ << endl;
		cout << Child::protected_member_ << endl;
	}
};

int main()
{
	Child test;
	test.doSomething();

    return 0;
}

