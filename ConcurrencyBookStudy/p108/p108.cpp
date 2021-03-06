#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;

mutex mutex_;
condition_variable condVar;

bool dataReady{ false };

void doTheWork()
{
	cout << "Processing shared data." << endl;
}

void waitingForWork()
{
	cout << "Worker : waiting for work." << endl;
	
	unique_lock<std::mutex> lck(mutex_);
	
	condVar.wait(lck, [] {return dataReady; });
	
	doTheWork();
	
	cout << "Work, done" << endl;
}

void setDataReady()
{
	this_thread::sleep_for(chrono::milliseconds(1000));

	{
		lock_guard<std::mutex> lck(mutex_);
		dataReady = true;
	}

	cout << "Sender: data is ready." << endl;
	condVar.notify_one();
}

int main()
{
	thread t1(waitingForWork);
	thread t2(setDataReady);

	t1.join();
	t2.join();

	cout << endl;
}
