#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

struct CriticalData
{
	mutex mut;
};

void deadLock(CriticalData & a, CriticalData & b)
{
	unique_lock<mutex> guard1(a.mut, defer_lock);
	cout << "Thread : " << this_thread::get_id() << " first mutex" << endl;

	this_thread::sleep_for(chrono::milliseconds(1));

	unique_lock<mutex> guard2(b.mut, defer_lock);
	cout << "Thread : " << this_thread::get_id() << " second mutex" << endl;

	cout << "Thread : " << this_thread::get_id() << " got both mutex" << endl;
	lock(guard1, guard2);
}

int main()
{
	CriticalData c1, c2;

	thread t1([&] {deadLock(c1, c2); });
	thread t2([&] {deadLock(c2, c1); });

	t1.join();
	t2.join();

	cout << endl;

}

