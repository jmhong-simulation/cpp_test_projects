#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;

mutex mutex_;
condition_variable condVar;

bool dataReady{ false };

void waitingForWork() 
{
	cout << "Worker : waiting for work. " << endl;

	unique_lock<mutex> lck(mutex_);
	condVar.wait(lck);

	cout << "Work done" << endl;
}

void setDataReady()
{
	condVar.notify_one();
}

int main()
{
	cout << endl;

	thread t1(setDataReady);
	thread t2(waitingForWork);

	t1.join();
	t2.join();

	cout << endl;
}

