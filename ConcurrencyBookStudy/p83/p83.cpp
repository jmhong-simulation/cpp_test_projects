#include <iostream>
#include <chrono>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

class Worker
{
private:
	string name;

public:
	Worker(string n)
		: name(n)
	{}

	void operator() ()
	{
		for (int i = 1; i <= 3; ++i)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << name << " : " << "Work " << i << " done !!!" << endl;
		}
	}
};

int main()
{
	cout << endl;
	cout << "Boss : let's start working." << endl;

	thread a1 = thread(Worker("A"));
	thread a2 = thread(Worker("B"));
	thread a3 = thread(Worker("C"));

	a1.join();
	a2.join();
	a3.join();
}


