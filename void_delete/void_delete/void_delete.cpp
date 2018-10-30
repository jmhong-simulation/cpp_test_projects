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
Note: deleting void doesn't call destructor
*/
int main()
{
	LargeData *data = new LargeData;
	delete data; // LargeData destructor called

	Container *cont = new Container;

	Worker worker;
	worker.work(cont);

	cont->deleteMemory(); // LargeData destructor not called

    std::cout << "Hello World!\n"; 
}
