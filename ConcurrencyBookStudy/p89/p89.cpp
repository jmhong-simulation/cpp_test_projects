#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

struct CriticalData
{
	mutex mut;
};

void deadLock(CriticalData & a, CriticalData & b)
{
	a.mut.lock();
	cout << "Get the first mutex" << endl;
	this_thread::sleep_for(std::chrono::milliseconds(1));
	
	b.mut.lock();
	cout << "Get the second mutex" << endl;

	// do something with a and b

	a.mut.unlock();
	b.mut.unlock();
}

int main()
{
	CriticalData c1;
	CriticalData c2;

	thread t1([&] {deadLock(c1, c2); });
	thread t2([&] {deadLock(c2, c1); }); // deadlock

	t1.join();
	t2.join();
}

