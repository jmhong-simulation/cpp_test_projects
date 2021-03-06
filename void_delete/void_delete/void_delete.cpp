#include <iostream>

class Container
{
public:
	void * data_ptr = nullptr;

	void deleteMemory()
	{
		if (data_ptr != nullptr) delete data_ptr;
	}
};

class LargeData
{
public:
	double data[200000000];

	~LargeData()
	{
		std::cout << "Destructor" << std::endl;
	}
};

class Worker
{
public:
	void work(Container *&cont)
	{
		cont->data_ptr = new LargeData;
	}
};

/*

Notes
1. void pointer knows the size
2. deleting void doesn't call destructor

https://stackoverflow.com/questions/941832/is-it-safe-to-delete-a-void-pointer

*/

int main()
{
	using namespace std;

	{
		cout << "Destructor called (default)" << endl;
		LargeData *data = new LargeData;
		delete data; // LargeData destructor called
		cout << endl;
	}

	{
		cout << "Destructor NOT called" << endl;
		void *data = new LargeData;
		delete data; // LargeData destructor called
		cout << endl;		
	}

	{
		cout << "Destructor called after casting" << endl;
		void *data = new LargeData;
		delete static_cast<LargeData*>(data); // LargeData destructor called
		cout << endl;
	}

	Container *cont = new Container;

	Worker worker;
	worker.work(cont);

	cont->deleteMemory(); // LargeData destructor not called

    std::cout << "Hello World!\n"; 
}
