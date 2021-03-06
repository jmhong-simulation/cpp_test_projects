#include <iostream>
#include <future>
#include <thread>
#include <utility>

using namespace std;

void product(promise<int>&& intPromise, int a, int b)
{
	intPromise.set_value(a * b);
}

struct Div
{
	void operator () (promise<int> && intPromise, int a, int b) const
	{
		intPromise.set_value(a / b);
	}
};

int main()
{
	int a = 20;
	int b = 10;

	promise<int> prodPromise;
	promise<int> divPromise;

	future<int> prodResult = prodPromise.get_future();
	future<int> divResult = divPromise.get_future();

	thread prodThread(product, std::move(prodPromise), a, b);
	
	Div div;
	thread divThread(div, std::move(divPromise), a, b);

	cout << prodResult.get() << endl;
	cout << divResult.get() << endl;

	prodThread.join();
	divThread.join();

	return 0;
}

