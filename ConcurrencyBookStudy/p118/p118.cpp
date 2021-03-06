#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
	// fire and forget mode
	{
		async(launch::async, [] {
			this_thread::sleep_for(chrono::seconds(2));
			cout << "First" << endl;
		});

		async(launch::async, [] {
			this_thread::sleep_for(chrono::seconds(0));
			cout << "Second" << endl;
		});

		cout << "Main" << endl;
	}

	{
		auto f1 = async(launch::async, [] {
			this_thread::sleep_for(chrono::seconds(2));
			cout << "First" << endl;
		});

		auto f2 = async(launch::async, [] {
			this_thread::sleep_for(chrono::seconds(0));
			cout << "Second" << endl;
		});

		cout << "Main" << endl;

		f1.get();
		f2.get();
	}
}

