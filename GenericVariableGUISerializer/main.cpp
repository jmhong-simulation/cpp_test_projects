#include <iostream>
#include "Serializer\Serializer.h"
#include "Serializer\ParametersControlForm.h"

using namespace std;
using namespace serializer;

class SimpleWorker
{
public:
	bool continue_ = true;
	int  count = 0;

	Serializer serializer;

	SimpleWorker()
	{
		//serializer.beginTab("Default");
		//serializer.beginGroup("SimpleWorker");
		serializer.add("continue", continue_);
		serializer.add("count", count);
	}

	void work()
	{
		if (continue_)
		{
			cout << "Working " << count << endl;
			count++;
		}
	}
};

int main()
{
	SimpleWorker worker;

	ParametersControlForm test_widget("Parameter Control Window");

	test_widget.addVariables(worker.serializer);
	test_widget.show_and_exec();

	while (true)
	{
		worker.work();
	}

	return 0;
}