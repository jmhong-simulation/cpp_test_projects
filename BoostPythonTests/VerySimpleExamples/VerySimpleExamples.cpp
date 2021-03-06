// BoostPythonTests.cpp : Defines the entry point for the console application.
//

#define BOOST_PYTHON_STATIC_LIB
#define BOOST_LIB_NAME "boost_numpy"
#include <boost/config/auto_link.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>

// for conveinece.
namespace py = boost::python;
namespace np = boost::python::numpy;

int main()
{
	using namespace std;

	Py_SetPythonHome(L"C:/Anaconda3/envs/py35tf12");

	Py_Initialize();
	np::initialize();

	py::object main_module = py::import("__main__");
	py::object main_namespace = main_module.attr("__dict__");

	py::object sys_ = py::import("sys");
	std::string version = py::extract<std::string>(sys_.attr("version"));
	std::cout << version << std::endl;

	// builtins! https://stackoverflow.com/questions/22674774/get-single-element-from-a-boostpythonobject-list-for-use-in-python-routine
	// there are more of good examples
	py::object print = py::import("__main__").attr("__builtins__").attr("print");
	py::object type = py::import("__main__").attr("__builtins__").attr("type");
	print("Hello, Python");

	// accessing elements of np arrays
	const auto shape = py::make_tuple(3, 2);
	np::ndarray ae_np = np::zeros(shape, np::dtype::get_builtin<float>());
	int count = 123;
	for(int i = 0; i < shape[0]; ++i)
		for (int j = 0; j < shape[1]; ++j)
		{
			ae_np[i][j] = (float)count++;
		}

	print(ae_np);
	print(type(ae_np));

	for (int i = 0; i < shape[0]; ++i)
		for (int j = 0; j < shape[1]; ++j)
		{
			std::cout << py::extract<float>(ae_np[i][j]) << std::endl;
		}

	// tensorflow test
	PyRun_SimpleString("import sys\n"
		"sys.argv = ['']"); // Tensorflow requires this to be initialized

	// examples from https://www.datacamp.com/community/tutorials/tensorflow-tutorial#gs.7CN1YdQ

	const py::object tf_ = py::import("tensorflow");

	const np::ndarray d1 = np::array(py::make_tuple(1.0f, 2.0f, 3.0f, 4.0f));
	const np::ndarray d2 = np::array(py::make_tuple(5.0f, 6.0f, 7.0f, 9.0f));

	const py::object x1 = tf_.attr("constant")(d1);
	const py::object x2 = tf_.attr("constant")(d2);

	const py::object result = tf_.attr("multiply")(x1, x2);
	const py::object sess = tf_.attr("Session")();

	print(sess.attr("run")(result));

	sess.attr("close")();

	return 0;
}

