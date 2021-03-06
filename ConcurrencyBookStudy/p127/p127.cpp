#include <iostream>
#include <future>
#include <thread>
#include <utility>

using namespace std;

mutex coutMutex;

struct Div
{
	void operator()(promise<int> && intPromise, int a, int b)
	{
		intPromise.set_value(a / b);
	}
};

struct Requestor
{
	void operator() (shared_future<int> shaFut)
	{
		lock_guard<mutex> coutGuard(coutMutex);

		cout << this_thread::get_id() << endl;
		cout << shaFut.get() << endl;
	}
};

int main()
{
	promise<int> divPromise;

	shared_future<int> divResult = divPromise.get_future();

	Div div;
	std::thread divThread(div, std::move(divPromise), 20, 10);

	Requestor req;
	thread sharedThread1(req, divResult);
	thread sharedThread2(req, divResult);
	thread sharedThread3(req, divResult);
	thread sharedThread4(req, divResult);

	divThread.join();

	sharedThread1.join();
	sharedThread2.join();
	sharedThread3.join();
	sharedThread4.join();

	return 0;
}
