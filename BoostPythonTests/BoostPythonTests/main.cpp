// BoostPythonTests.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>

#define BOOST_PYTHON_STATIC_LIB
#define BOOST_LIB_NAME "boost_numpy"
#include <boost/config/auto_link.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>


// from http://stackoverflow.com/questions/1418015/how-to-get-python-exception-text
#define PY_TRY			try {
#define PY_CATCH		} catch (py::error_already_set &) \
						{\
							if (PyErr_Occurred()) {\
								std::string msg = pyw.handle_pyerror();\
								std::cout << msg << std::endl;\
								exit(1);\
						} /*py_exception = true;bp::handle_exception();PyErr_Clear();*/ \
						}

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

		PythonCpp(wchar_t* home_path = L"C:/Anaconda3/envs/py35tf12")
		{
			Py_SetPythonHome(home_path);

			Py_Initialize();
			np::initialize();

			main_module_ = py::import("__main__");
			main_namespace_ = main_module_.attr("__dict__");			
			sys_ = py::import("sys");
			builtins_ = main_module_.attr("__builtins__");
			print_ = builtins_.attr("print");

			PyRun_SimpleString("import sys\n"
				"sys.argv = ['']"); // Tensorflow requires this to be initialized

			//sys_.attr("path").attr("append")("C:/Anaconda3/envs/py35tf12");
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

		template<typename ... Args>
		py::object type(Args ... args) const
		{
			return builtins_.attr("type")(args ...);
		}

		std::string handle_pyerror()
		{
			using namespace boost::python;
			using namespace boost;

			PyObject *exc, *val, *tb;
			object formatted_list, formatted;
			PyErr_Fetch(&exc, &val, &tb);
			handle<> hexc(exc), hval(allow_null(val)), htb(allow_null(tb));
			object traceback(import("traceback"));
			if (!tb) {
				object format_exception_only(traceback.attr("format_exception_only"));
				formatted_list = format_exception_only(hexc, hval);
			}
			else {
				object format_exception(traceback.attr("format_exception"));
				formatted_list = format_exception(hexc, hval, htb);
			}
			formatted = str("\n").join(formatted_list);
			return extract<std::string>(formatted);
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
		py::object tf_;
		py::object sess_;

		TensorflowCpp()
		{
			tf_ = py::import("tensorflow");
			sess_ = tf_.attr("Session")();
		}

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

namespace deeplearning
{
	class NeuralNetwork
	{
	public:
		boost::python::object backend_;	// tensorflow, maybe

		/*void forward(numpy) {}
		void backward(numpy) {}*/
	};

	// implement higher level NN and use PyNeuralNetwork ? of TensorflowNeuralNetwork ?
}

// https://stackoverflow.com/questions/41323576/attributeerror-due-to-sys-argv0-for-import-tensorflow-as-tf-inside-c
// tensorflow needs sys.argv.

int main(int argc, char *argv[])
{
	using namespace pycpp;

	PythonCpp pyw;

	cout << pyw.version() << endl;

	// examples from https://www.datacamp.com/community/tutorials/tensorflow-tutorial#gs.7CN1YdQ

	const np::ndarray d1 = pycpp::NumpyCpp::make_array(1.0f, 2.0f, 3.0f, 4.0f);
	const np::ndarray d2 = pycpp::NumpyCpp::make_array(5.0f, 6.0f, 7.0f, 8.0f);

	pyw.print(d1);
	pyw.print(d2);

	auto os = py::import("os");
	pyw.print(os.attr("getcwd")());
	os.attr("chdir")("C:/Anaconda3/envs/py35tf12");
	pyw.print(os.attr("getcwd")());

	pyw.sys_.attr("path").attr("append")("C:/Anaconda3/envs/py35tf12");
	pyw.sys_.attr("path").attr("append")("D:\\github-repository\\cpp_test_projects\\BoostPythonTests\\BoostPythonTests");

	auto jm_module = py::import("JMModule");
	jm_module.attr("test_func")();

	return 0;

	TensorflowCpp tfc;

	// simple tensorflow test
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
	
	PY_TRY{
		nodes.append(mult);
		nodes.append(add);
	}PY_CATCH;

	pyw.print(nodes);

	auto result_list = tfc.run(nodes);

	pyw.print(result_list);
	pyw.print(pyw.builtins_.attr("type")(result_list));

	py::list rl = py::extract<py::list>(result_list);

	cout << py::len(rl) << endl;

	for (int i = 0; i < py::len(rl); ++i)
	{
		pyw.print(pyw.builtins_.attr("type")(py::object(rl[i])));
		const np::ndarray arr = py::extract<np::ndarray>(rl[i]);
		
		pyw.print(arr);
	}
	
	// tensorflow None shape test
	{
		py::list shape;
		shape.append(py::eval("None"));
		shape.append(1);
		shape.append(1);

		// nodes
		py::object f32 = tfc.tf_.attr("float32");
		py::object x_input = tfc.tf_.attr("placeholder")(f32, shape);
		py::object y_target = tfc.tf_.attr("placeholder")(f32, shape);
		py::object temp = tfc.tf_.attr("layers").attr("dense")(x_input, 1);
		py::object loss = tfc.tf_.attr("losses").attr("mean_squared_error")(temp, y_target);
		py::object train = tfc.tf_.attr("train").attr("AdamOptimizer")(1e-1).attr("minimize")(loss);

		np::dtype dtype32 = np::dtype::get_builtin<float>();
		np::ndarray x_data = np::zeros(py::make_tuple(1, 1, 1), dtype32);
		((float*)(x_data.get_data()))[0] = 1.0f;
		np::ndarray y_data = np::zeros(py::make_tuple(1, 1, 1), dtype32);
		((float*)(y_data.get_data()))[0] = 1.0f;

		py::object init_op = tfc.tf_.attr("global_variables_initializer")();

		tfc.sess_.attr("run")(init_op);

		py::list nodes_to_run;
		nodes_to_run.append(temp);
		nodes_to_run.append(loss);
		nodes_to_run.append(train);

		py::dict feed_dict;
		feed_dict[x_input] = x_data;
		feed_dict[y_target] = y_data;

		for(int i = 0; i < 10; ++i)
		{
			py::list output = py::extract<py::list>(tfc.sess_.attr("run")(nodes_to_run, feed_dict));
			py::object y_out_obj = py::extract<py::object>(output[0]);			
			const np::ndarray y_out = np::from_object(y_out_obj);
			const float loss = py::extract<float>(output[1]);

			cout << ((float*)y_out.get_data())[0] << " ";
			cout << loss << endl;
		}
	}

    return 0;
}

