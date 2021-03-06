#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

class Point
{
public:
	int m_int;
	string m_str;
	double m_double;
	int* m_ptr;

	Point(const int &_int, const string&_str, const double & _double, int * const _ptr)
		: m_int(_int), m_str(_str), m_double(_double), m_ptr(_ptr)
	{}
};

class Point2
{
public:
	int m_int;
	string m_str;
	double m_double;
	//int* m_ptr;

	Point2(const int &_int, const string&_str, const double & _double)
		: m_int(_int), m_str(_str), m_double(_double)
	{
		//cout << "Constructor " << m_int << endl;
	}

	//Point2(Point2 & _pt)
	//{
	//	cout << "copy " << _pt.m_int << endl;
	//}

	//Point2(Point2 && _pt)
	//{
	//	cout << "move " << _pt.m_int << endl;
	//	m_int = _pt.m_int;
	//}
};

int main()
{
	using second_t = chrono::duration<double, std::ratio<1>>;
    
	{
		int value = 5;
		int *ptr = &value;

		auto start_time = chrono::high_resolution_clock::now();

		vector<Point2> push_vector;

		push_vector.reserve(10000000);
		for (unsigned i = 0; i < 10000000; ++i)
			push_vector.push_back({ (int)i, "Push", 3.0 });

		auto end_time = chrono::high_resolution_clock::now();

		cout << chrono::duration_cast<second_t>(end_time - start_time).count() << endl;
	}

	{
		int value = 5;
		int *ptr = &value;

		auto start_time = chrono::high_resolution_clock::now();

		vector<Point2> emplace_vector;
		emplace_vector.reserve(10000000);
		for (unsigned i = 0; i < 10000000; ++i)
			emplace_vector.emplace_back(i, "emplace", 3.0);

		auto end_time = chrono::high_resolution_clock::now();

		cout << chrono::duration_cast<second_t>(end_time - start_time).count() << endl;
	}

	



}

