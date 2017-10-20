#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>

using namespace std;

/* TODO
- test with print(), print(one parameter), print(two parameters)
- test with lambda function
*/


class GenericFunctionPointerBase
{
public:
	virtual void invoke() = 0;
};

template<class T_CLASS, class T_FUNC, class ... Args>
class GenericFunctionPointer : public GenericFunctionPointerBase
{
public:
	T_CLASS *instance_ptr;
	T_FUNC func_ptr;

	//template<class ... TT>
	//void do_something(TT ... par)
	//{
	//	cout << par << endl;
	//}

	GenericFunctionPointer(T_CLASS* _inst_ptr, T_FUNC _func_ptr, Args ... args)
	{
		instance_ptr = _inst_ptr;
		func_ptr = _func_ptr;

		//do_something(args ... );
	}

	void invoke()
	{
		((*instance_ptr).*func_ptr)();
	}
};

template<class T_FUNC>
GenericFunctionPointerBase *makePtr(T_FUNC _func)
{
	auto ptr = new GenericFunctionPointer<T>;
	ptr->func = _func;

	return ptr;
}

class Worker
{
public:

	Worker()
	{
		// registerEvent("save", this->save);
		//GenericFunctionPointerBase *ptr_prt = new GenericFunctionPointer < Worker, void (Worker::*)()>(this, &Worker::print);
		//GenericFunctionPointerBase *ptr_prt = new GenericFunctionPointer < Worker, void (Worker::*)()>(this, []() {cout << __FUNCTION__ << endl; });
		//ptr_prt->invoke();

		/*std::function<void()> func = []() {cout << __FUNCTION__ << endl; };
		func();

		std::function<void(Worker*)> member_func = &Worker::print;
		member_func(this);*/

		/*std::function<void(Worker*, const std::string&)> member_func2 = &Worker::save;
		member_func2(this, string("Hello Save file anme"));*/

		/*std::function<void()> member_func2 = std::bind([](Worker* ptr, const string& input_str) {ptr->save(input_str);}, this);
		member_func2(string("Input string "));*/

		// https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
		function<void(const string&)> f = [this](const string& input_string) {
			this->save(input_string);
		};

		f("hello lambda");

		/*auto collab = std::mem_fn(&Worker::save); // mem_fn will be removed
		collab(this, "hello");*/
	}

	void save(const string& filename)
	{
		cout << filename << "saved" << endl;
	}

	void print()
	{
		cout << __FUNCTION__ << endl;
	}

};


int main()
{
	Worker test_worker;

	//typedef  void (Worker::*FUNC_TYPE)();  // Please do this!
	//FUNC_TYPE p = &Worker::print;
	//std::invoke(p, &test_worker); // https://isocpp.org/wiki/faq/pointers-to-members

	/*void (Worker::*func_ptr)() = &Worker::print;

	((test_worker).*func_ptr)();*/

	/*GenericFunctionPointerBase *ptr_prt = new GenericFunctionPointer < Worker, void (Worker::*)()> (&test_worker, &Worker::print);
	ptr_prt->invoke();*/

	//GenericFunctionPointer<Worker, void (Worker::*)()> generic_fp(&test_worker, &Worker::print);
	//generic_fp.invoke();

	return 0;
}