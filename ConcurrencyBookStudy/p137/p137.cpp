#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <numeric> // std::accumulate
#include <mutex>
#include <atomic>

using namespace std;

constexpr long long size = 100000000;

int main()
{
	std::vector<int> randValues;
	randValues.reserve(::size);

	random_device seed;

	mt19937 engine(seed());

	uniform_int_distribution<> uniformDist(1, 10);

	for (long long i = 0; i < ::size; ++i)
		randValues.push_back(uniformDist(engine));

	cout << "Start" << endl;

	cout << "Simple for loop" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum{ 0 };
		for (auto n : randValues) sum += n; //0.385971, 5500030214

		const std::chrono::duration<double> dur = 
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	
	std::cout << "std::accumulate" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		const unsigned long long sum = 
		std::accumulate(randValues.begin(), randValues.end(), 0ull); // 0.334055, 5499840861

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	std::cout << "Lock guard" << endl;
	{
		std::mutex myMutex;
		unsigned long long sum{ 0 };

		const auto sta = chrono::steady_clock::now();

		for (auto i : randValues)
		{
			lock_guard<mutex> myLockGuard(myMutex);
			sum += i;
		}

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;

		cout << sum << endl;
		cout << endl;
	}

	std::cout << "Atomics += " << endl;
	{
		std::atomic<unsigned long long>	sum{ 0 };

		std::cout << std::boolalpha;
		std::cout << "Lock free " << sum.is_lock_free() << endl;

		const auto sta = chrono::steady_clock::now();

		for (auto i : randValues)
		{
			sum += i;
		}

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;

		cout << sum << endl;
		cout << endl;
	}

	std::cout << "Atomics fetch add" << endl;
	{
		std::atomic<unsigned long long>	sum{ 0 };

		std::cout << std::boolalpha;
		std::cout << "Lock free " << sum.is_lock_free() << endl;

		const auto sta = chrono::steady_clock::now();

		for (auto i : randValues)
		{
			sum.fetch_add(i);
		}

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;

		cout << sum << endl;
		cout << endl;
	}
	

	return 0;
}
