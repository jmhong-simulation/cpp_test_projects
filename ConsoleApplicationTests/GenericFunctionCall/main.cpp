#include <iostream>
#include <string>
#include <thread>
#include "TestWorker.h"
#include "TestGUI.h"

using namespace std;

TestGUI *gui = nullptr;

int main()
{
	auto gui_thread = std::thread([=] {gui = new TestGUI; });

	TestWorker worker;

	while (true)
	{
		if (worker.is_continue) worker.update();
		else cout << "Not working" << endl;

		std::this_thread::sleep_for(100ms);
	}

	return 0;
}