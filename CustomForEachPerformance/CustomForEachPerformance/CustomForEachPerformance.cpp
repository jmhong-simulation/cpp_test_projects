#include <chrono>
#include <string>
#include <iostream>
#include <random>
#include <glm/glm.hpp>
#include <execution>
#include <vector>

/*

Result: using lambda in for loop was faster. do whatever you feel conveniet to you. Compiler will optimize it.

*/

using namespace std;

template<typename T_FUNC>
void checkTime(const string & func_name, T_FUNC func)
{
	cout << func_name << endl;
	
	const auto start_time = chrono::high_resolution_clock::now();
	
	func();
	
	const auto end_time = chrono::high_resolution_clock::now();

	const auto dur = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

	cout << "Elapsed time = " << dur.count() / 1000.0 << " s " << endl;
}

class Circle
{
public:
	glm::dvec3 center;

	double getValue(const glm::dvec3 & point)
	{
		return glm::distance(point, center);
	}
};

int main()
{
	//checkTime("Print Hello World", []() {for (int i = 0; i < 100; ++i) cout << "Hello, World " << endl; });

	random_device seed;
	mt19937 engine(seed());

	std::uniform_real_distribution<double> uniform_dist(-1.0, 1.0);

	const unsigned n_data = 100'000'000;

	vector<glm::dvec3> points;
	points.resize(n_data);

	checkTime("Initialize data ", [&]() {
		std::for_each(std::execution::par, points.begin(), points.end(), [&](glm::dvec3 & v)
		{
			v = glm::dvec3({ uniform_dist(engine), uniform_dist(engine), uniform_dist(engine) });
		}); });

	/*for (unsigned i = 0; i < n_data; ++i)
		points.push_back({ uniform_dist(engine), uniform_dist(engine), uniform_dist(engine) });*/

	Circle cir;

	checkTime("Naive", [&]() {
		double temp = 1.0;
		for (unsigned i = 0; i < n_data; ++i)
			temp += cir.getValue(points[i]);
		cout << temp << endl;
	});

	checkTime("Lambda in lambda", [&]() {

		double temp = 1.0;

		auto lambda = [&](const unsigned & i) {
			temp += cir.getValue(points[i]);
		};

		for (unsigned i = 0; i < n_data; ++i)
			lambda(i);

		cout << temp << endl;
	});
}

