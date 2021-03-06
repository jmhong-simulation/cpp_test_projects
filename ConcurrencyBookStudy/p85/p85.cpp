#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;

mutex coutMutex;

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
			
			coutMutex.lock();
			cout << name << " : " << "Work " << i << " done !!!" << endl;
			coutMutex.unlock();
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
