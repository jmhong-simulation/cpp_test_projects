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
};

class Worker
{
public:
	void work(Container *&cont)
	{
		cont->data_ptr = new LargeData;
	}
};

int main()
{
	Container *cont = new Container;

	Worker worker;
	worker.work(cont);

	cont->deleteMemory();

    std::cout << "Hello World!\n"; 
}
