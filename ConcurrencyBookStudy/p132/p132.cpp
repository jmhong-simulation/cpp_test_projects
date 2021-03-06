#include <iostream>
#include <future>
#include <utility>

using namespace std;

void doTheWork()
{
	cout << "Processing shared data" << endl;
}

void waitingForWork(std::future<void> && fut)
{
	cout << "Waiting for work" << endl;
	fut.wait(); // wait for prom.set_value()
	doTheWork();
	cout << "Work done" << endl;
}

void setDataReady(promise<void> && prom)
{
	cout << "Data is ready" << endl;
	prom.set_value();
}

int main()
{
	promise<void> sendReady;
	auto fut = sendReady.get_future();

	thread t1(waitingForWork, move(fut));
	thread t2(setDataReady, move(sendReady));

	t1.join();
	t2.join();
}

