#include <iostream>
#include <future>
#include <thread>

using namespace std;

int main()
{
	cout << endl;

	int res;

	thread t([&] {res = 2000 + 11; });
	t.join();

	cout << res << endl;

	auto fut = std::async([&] {return 2000 + 11; });
	cout << fut.get() << endl;

	cout << endl;
}

