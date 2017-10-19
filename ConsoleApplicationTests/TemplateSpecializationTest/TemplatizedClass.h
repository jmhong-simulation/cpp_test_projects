#pragma once

template<class TT>
class TemplatizedClass
{
public:

	TT templatized_worker;

	void work()
	{
		templatized_worker.printName();
	}
};

