#include <iostream>
#include <utility>
#include <future>
#include <iostream>
#include <thread>
#include <deque>

using namespace std;

class SumUp
{
public:
	auto operator()(int beg, int end)
	{
		long long int sum(0);
		for (int i = beg; i < end; ++i)
			sum += i;
		return sum;
	}
};

int main()
{
	SumUp s1, s2, s3, s4;

	std::packaged_task<long long(int, int)> st1(s1);
	std::packaged_task<long long(int, int)> st2(s2);
	std::packaged_task<long long(int, int)> st3(s3);
	std::packaged_task<long long(int, int)> st4(s4);

	std::future<long long> f1 = st1.get_future();
	std::future<long long> f2 = st2.get_future();
	std::future<long long> f3 = st3.get_future();
	std::future<long long> f4 = st4.get_future();

	std::deque<std::packaged_task<long long(int, int)>> allTasks;
	allTasks.push_back(std::move(st1));
	allTasks.push_back(std::move(st2));
	allTasks.push_back(std::move(st3));
	allTasks.push_back(std::move(st4));

	int begin{ 1 };
	int increment{ 2500 };
	int end = begin + increment;

	while (not allTasks.empty())
	{
		std::packaged_task<long long(int, int)> myTask
			= std::move(allTasks.front());

		allTasks.pop_front();

		std::thread sumThread(std::move(myTask), begin, end);

		begin = end;

		end += increment;

		sumThread.detach();
	}


	auto sum = f1.get() + f2.get() + f3.get() + f4.get();

	cout << sum << endl;

	return 1;
}


