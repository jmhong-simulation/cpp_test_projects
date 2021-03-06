#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <atomic>
#include <future>

using namespace std;

constexpr long long n_data = 100'000'000;

constexpr long long fir = n_data / 4 * 1;
constexpr long long sec = n_data / 4 * 2;
constexpr long long thi = n_data / 4 * 3;
constexpr long long fou = n_data / 4 * 4;

mutex myMutex;

void sumUp(unsigned long long & sum, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	for (auto it = beg; it < end; ++it)
	{
		sum += val[it];
	}
}

void sumUpLockLocalSum(unsigned long long & sum, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	unsigned long long tmpSum{};

	for (auto it = beg; it < end; ++it)
	{
		tmpSum += val[it];
	}

	lock_guard<std::mutex> myLock(myMutex);
	sum += tmpSum;
}

void sumUpLock(unsigned long long & sum, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	for (auto it = beg; it < end; ++it)
	{
		lock_guard<std::mutex> myLock(myMutex);
		sum += val[it];
	}
}

void sumUpAtomic(std::atomic<unsigned long long> & sum, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	for (auto it = beg; it < end; ++it)
	{
		//sum += val[it];
		sum.fetch_add(val[it]);
	}
}

thread_local unsigned long long tmpSum = 0;

void sumUpAtomicLocalSum(std::atomic<unsigned long long> & sum, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	//unsigned long long tmpSum{};

	for (auto it = beg; it < end; ++it)
	{
		//sum += val[it];
		tmpSum += (val[it]);
	}

	sum.fetch_add(tmpSum, std::memory_order_relaxed);
}

void sumUpAtomicRelaxed(std::atomic<unsigned long long> & sum, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	for (auto it = beg; it < end; ++it)
	{
		//sum += val[it];
		sum.fetch_add(val[it], std::memory_order_relaxed);
	}
}

void sumUpPromise(promise<unsigned long long> && prom, const std::vector<int> & val,
	unsigned long long beg, unsigned long long end)
{
	unsigned long long sum = {};
	for (auto i = beg; i < end; ++i)
	{
		sum += val[i];
	}
	prom.set_value(sum);
}

int main()
{

	std::vector<int> randValues;
	randValues.reserve(n_data);

	random_device seed;

	mt19937 engine(seed());

	uniform_int_distribution<> uniformDist(1, 10);

	for (long long i = 0; i < n_data; ++i)
		randValues.push_back(uniformDist(engine));

	cout << "Naive" << endl;
	{
		unsigned long long sum = 0;

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUp, std::ref(sum), std::ref(randValues), 0, fir);
		thread t2(sumUp, std::ref(sum), std::ref(randValues), fir, sec);
		thread t3(sumUp, std::ref(sum), std::ref(randValues), sec, thi);
		thread t4(sumUp, std::ref(sum), std::ref(randValues), thi, fou);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	cout << "Lock guard" << endl;
	{
		unsigned long long sum = 0;

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUpLock, std::ref(sum), std::ref(randValues), 0, fir);
		thread t2(sumUpLock, std::ref(sum), std::ref(randValues), fir, sec);
		thread t3(sumUpLock, std::ref(sum), std::ref(randValues), sec, thi);
		thread t4(sumUpLock, std::ref(sum), std::ref(randValues), thi, fou);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	cout << "Atomic fetch_add" << endl;
	{
		std::atomic<unsigned long long> sum = 0;

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUpAtomic, std::ref(sum), std::ref(randValues), 0, fir);
		thread t2(sumUpAtomic, std::ref(sum), std::ref(randValues), fir, sec);
		thread t3(sumUpAtomic, std::ref(sum), std::ref(randValues), sec, thi);
		thread t4(sumUpAtomic, std::ref(sum), std::ref(randValues), thi, fou);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	cout << "Atomic relaxed semantic" << endl;
	{
		std::atomic<unsigned long long> sum = 0;

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUpAtomicRelaxed, std::ref(sum), std::ref(randValues), 0, fir);
		thread t2(sumUpAtomicRelaxed, std::ref(sum), std::ref(randValues), fir, sec);
		thread t3(sumUpAtomicRelaxed, std::ref(sum), std::ref(randValues), sec, thi);
		thread t4(sumUpAtomicRelaxed, std::ref(sum), std::ref(randValues), thi, fou);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	cout << "Lock guard LocalSum" << endl;
	{
		unsigned long long sum = 0;

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUpLockLocalSum, std::ref(sum), std::ref(randValues), 0, fir);
		thread t2(sumUpLockLocalSum, std::ref(sum), std::ref(randValues), fir, sec);
		thread t3(sumUpLockLocalSum, std::ref(sum), std::ref(randValues), sec, thi);
		thread t4(sumUpLockLocalSum, std::ref(sum), std::ref(randValues), thi, fou);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	cout << "Atomic Local Sum" << endl;
	{
		std::atomic<unsigned long long> sum = 0;

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUpAtomicLocalSum, std::ref(sum), std::ref(randValues), 0, fir);
		thread t2(sumUpAtomicLocalSum, std::ref(sum), std::ref(randValues), fir, sec);
		thread t3(sumUpAtomicLocalSum, std::ref(sum), std::ref(randValues), sec, thi);
		thread t4(sumUpAtomicLocalSum, std::ref(sum), std::ref(randValues), thi, fou);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	cout << "Promise" << endl;
	{
		promise<unsigned long long> prom1, prom2, prom3, prom4;

		auto fut1 = prom1.get_future();
		auto fut2 = prom2.get_future();
		auto fut3 = prom3.get_future();
		auto fut4 = prom4.get_future();

		const auto sta = chrono::steady_clock::now();

		thread t1(sumUpPromise, std::move(prom1), std::ref(randValues), 0, fir);
		thread t2(sumUpPromise, std::move(prom2), std::ref(randValues), fir, sec);
		thread t3(sumUpPromise, std::move(prom3), std::ref(randValues), sec, thi);
		thread t4(sumUpPromise, std::move(prom4), std::ref(randValues), thi, fou);

		auto sum = fut1.get() + fut2.get() + fut3.get() + fut4.get();

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		const std::chrono::duration<double> dur =
			chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;

	}

	return 0;
}
