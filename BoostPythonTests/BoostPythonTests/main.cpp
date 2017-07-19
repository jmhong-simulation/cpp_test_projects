// BoostPythonTests.cpp : Defines the entry point for the console application.
//

#define BOOST_PYTHON_STATIC_LIB
#define BOOST_LIB_NAME "boost_numpy"
#include <boost/config/auto_link.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>

namespace pycpp
{
	using namespace std;

	namespace py = boost::python;
	namespace np = boost::python::numpy;

	class PythonCpp
	{
	public:
		py::object main_module_;
		py::object main_namespace_;
		py::object builtins_;
		py::object sys_;
		py::object print_;

		PythonCpp(wchar_t* home_path = L"C:/Anaconda3/envs/py35tf1")
		{
			Py_SetPythonHome(home_path);

			Py_Initialize();
			np::initialize();

			main_module_ = py::import("__main__");
			main_namespace_ = main_module_.attr("__dict__");
			builtins_ = main_module_.attr("__builtins__");
			sys_ = py::import("sys");
			print_ = builtins_.attr("print");

			
		}

		string version() const
		{
			return py::extract<std::string>(sys_.attr("version"));			
		}

		// let's simply use print_(...) because this makes compile overhead unnecessarily.
		// However, it's happy to see working.
		template<typename ... Args>
		void print(Args ... args) const
		{
			this->print_(args ...);
		}
	};

	class NumpyCpp
	{
	public:
		template<typename ... Args>
		static np::ndarray make_array(Args ... args)
		{
			return np::array(py::make_tuple(args ...));
		}
	};

	class TensorflowCpp
	{
	public:
		const py::object tf_ = py::import("tensorflow");
		const py::object sess_ = tf_.attr("Session")();


		template<typename ... Args>
		py::object run(Args ... args)
		{
			return sess_.attr("run")(args ...);
		}

		template<typename ... Args>
		py::object add(Args ... args)
		{
			return tf_.attr("add")(args ...);
		}

		template<typename ... Args>
		py::object constant(Args ... args)
		{
			return tf_.attr("constant")(args ...);
		}

		template<typename ... Args>
		py::object multiply(Args ... args)
		{
			return tf_.attr("multiply")(args ...);
		}

		template<typename ... Args>
		py::object Session(Args ... args)
		{
			return tf_.attr("Session")(args ...);
		}
	};
}

int main()
{
	using namespace pycpp;

	PythonCpp pyw;

	cout << pyw.version() << endl;

	pyw.print_("Hello, Python");
	pyw.print("Hello, Python", 1234, 1234 * 2);

	// examples from https://www.datacamp.com/community/tutorials/tensorflow-tutorial#gs.7CN1YdQ

	const np::ndarray d1 = pycpp::NumpyCpp::make_array(1.0f, 2.0f, 3.0f, 4.0f);
	const np::ndarray d2 = pycpp::NumpyCpp::make_array(5.0f, 6.0f, 7.0f, 8.0f);

	pyw.print(d1);
	pyw.print(d2);

	TensorflowCpp tfc;
	const auto x1 = tfc.constant(d1);
	const auto x2 = tfc.constant(d2);

	const auto mult = tfc.multiply(x1, x2);
	pyw.print(mult);

	const auto add = tfc.add(x1, x2);
	pyw.print(add);

	auto result = tfc.run(mult);
	pyw.print("Mult result ", result);

	result = tfc.run(add);
	pyw.print("Add result ", result);

	py::list nodes;
	nodes.append(mult);
	nodes.append(add);

	//result = tfc.run(nodes);

	auto result_list = py::extract<py::list>(tfc.run(nodes));

	pyw.print(result_list);


    return 0;
}

