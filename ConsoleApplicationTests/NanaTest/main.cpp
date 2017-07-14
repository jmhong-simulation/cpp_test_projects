#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include "nlohmann\json.hpp"

#include <iostream>

using namespace std;
using namespace nana;

namespace scripting
{
	typedef enum { INT, FLOAT, DOUBLE, STRING, BOOL } VariableType;

	class VariableBase
	{
	public:
		string name_;
		VariableType type_;
	};

	template<class T>
	class Variable : public VariableBase
	{
	public:
		T &v_;

		Variable(T& _v)
			: v_(_v)
		{}
	};

	class Manager
	{
	public:
		map<string, VariableBase*> vars_;
		vector<VariableBase*> vars_vec_; // to remember order

		~Manager()
		{
			for (const auto& itr : vars_vec_)	delete itr;
		}

		void checkIntegrity(const string& name, const VariableType& vt)
		{
			// check if 'name' key exists
			if (vars_.count(name) == 0) {
				cout << __FUNCTION__ << endl;
				cout << "Key " << name << "Not found " << endl;
				exit(1);
			}

			// check if type is correct
			if (vars_[name]->type_ != vt) {
				cout << __FUNCTION__ << endl;
				cout << "Wrong type " << endl;
				exit(1);
			}
		}

		//TODO: implement addNew(..., int/float/double/string/bool)
		void addNew(const string& name, int& v)
		{
			if (vars_.count(name) > 0) {
				cout << __FUNCTION__ << endl;
				cout << "Key " << name << " already exists " << endl;
				exit(1);
			}

			VariableBase *new_var = new Variable<int>(v);

			new_var->name_ = name;
			new_var->type_ = VariableType::INT;

			vars_[name] = new_var;
			vars_vec_.push_back(new_var);
		}

		int& getInt(const string& name)
		{
			checkIntegrity(name, VariableType::INT);

			Variable<int> *var = (Variable<int>*)vars_[name];

			return var->v_;
		}

		//TODO: getFloat, getDouble, getString, getBool
	};
}

class TextBoxWrapper
{
public:
	textbox tbx_;	// (fm, rectangle{ 20, 20, 150, 30 });
	string text_;	// text buffer
	label lab_;

	TextBoxWrapper(const form& _fm, const rectangle& _rect_label, const rectangle& _rect_textbox)
		: lab_(_fm, _rect_label), tbx_(_fm, _rect_textbox)
	{
		lab_.caption("int res_x");
		lab_.text_align(align::left, align_v::center);

		tbx_.multi_lines(false);
		tbx_.caption("Hello, Textbox");
		tbx_.events().key_release([&](const nana::arg_keyboard& a_k) {
			if (a_k.key == 13) {
				cout << "Enter Key pressed " << endl;
				cout << this->text_ << endl;
			}
		});

		tbx_.events().text_changed([&](const nana::arg_textbox& a_b) {
			string text_line;
			a_b.widget.getline(0, text_line);
			text_ = text_line;
		});

		tbx_.getline(0, text_);

		cout << text_ << endl;
	}

	void foo(const nana::arg_keyboard& a_k)
	{
		if (a_k.key == 13)
		{
			cout << "Enter Key pressed " << endl;
		}
	}

};

using json = nlohmann::json;
using namespace scripting;

int main()
{
	json j, j2;
	
	j["type"] = "int";
	j["name"] = "x_res";
	j["value"] = "256";

	j2["variable"] = j;
	j2["variable2"] = j;

	// special iterator member functions for objects
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		//std::cout << it.key() << " : " << it.value() << "\n";
		cout << it.value().get<string>() << endl;
	}

	int test_int;
	Manager var_manager;
	var_manager.addNew("zebra", test_int);
	var_manager.addNew("test_int", test_int);
	var_manager.getInt("test_int") = 2048;
	cout << "test_int " << test_int << endl;

	for (const auto& itr : var_manager.vars_)
	{
		cout << itr.first << endl;
	}

	form fm;
	fm.caption(L"Hello, World!");

	TextBoxWrapper tbx(fm, rectangle{ 20, 20, 60, 20 }, rectangle{ 100, 20, 150, 20 });

	//textbox tbx(fm, rectangle{ 20, 20, 150, 30 });
	//tbx.caption("Hello, Textbox");
	///*tbx.set_highlight("sqlrev", colors::dark_blue, colors::yellow);
	//tbx.set_keywords("sqlrev", false, true, { "select", "from", "where" });*/
	//tbx.multi_lines(false);
	//tbx.events().key_release(foo);


	// add a button
	button btn(fm, rectangle{ 20, 50, 150, 30 });
	btn.caption(L"Quit");
	btn.events().click(API::exit);

	fm.show();
	exec();
}