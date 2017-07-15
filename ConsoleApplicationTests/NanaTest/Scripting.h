#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <typeinfo>
#include <sstream>      // std::stringstream
#include "nlohmann\json.hpp"

#define FATAL_ERROR(message) {cout << __FUNCTION__ << endl; cout << message << endl; assert(false); exit(1);}

//using json = nlohmann::json;

namespace scripting
{
	using namespace std;
	using namespace nlohmann;

	class VariableBase
	{
	public:
		string name_;
		string str_type_name_;

	public:
		template<class T>
		bool isType() { return str_type_name_ == typeid(T).name(); }

		virtual string getStrValue() = 0;
		//virtual void   setValueFromString(const string& str_value) = 0;
	};

	// We need this inherited class so that UI can modify variable directly without looking inside worker parts.
	template<class T>
	class Variable : public VariableBase
	{
	public:
		using VariableBase::name_;
		using VariableBase::str_type_name_;

		T &v_;

	public:
		Variable(T& _v)
			: v_(_v)
		{}

		string getStrValue()
		{
			stringstream ss;
			ss << v_;

			return ss.str();
		}

	/*	void setValueFromString(const string& str_value)
		{
			if (isType<int>()) v_ = str2int(str_value);
			else if (isType<float>()) v_ = str2float(str_value);
			else if (isType<bool>()) v_ = str2bool(str_value);
			else if (isType<string>()) v_ = str_value; // cannot be achieved because of this!
			else FATAL_ERROR("Type not defined " << str_type_name_);
		}

		int str2int(const string& str_value)
		{
			return stoi(str_value);
		}

		float str2float(const string& str_value)
		{
			return stof(str_value);
		}

		bool str2bool(const string& str_value)
		{
			return str_value != "0";
		}*/
	};

	class Category
	{
	public:
		string name_;	// name of this category

		vector<VariableBase*> vars_vec_;		// for ordered iteration

	public:
		Category(const string& _name);
		~Category();

		void dump()
		{
			cout << "Category " << name_ << endl;

			for (const auto& itr : vars_vec_)
			{
				cout << itr->str_type_name_ << " " << itr->name_ << " " << itr->getStrValue() << endl;
			}
		}

		bool checkIfNameExists(const string& name_key)
		{
			for (const auto& itr : vars_vec_) {
				if (itr->name_ == name_key) return true;
			}

			return false;
		}

		VariableBase* findByName(const string& key_name)
		{
			for (const auto& itr : vars_vec_) {
				if (itr->name_ == key_name)
					return itr;
			}
			
			FATAL_ERROR("Variable was not found.");

			return nullptr; // This should never happen
		}

		template<class T>
		void checkTypeName(const string& key_name)
		{
			if (findByName(key_name)->str_type_name_ != typeid(T).name()) FATAL_ERROR("Wrong type ");
		}

		template<class T>
		void checkIntegrity(const string& key_name)
		{
			// check if the same keys already exist
			if (checkIfNameExists(key_name)) FATAL_ERROR("Key " << name << " already exists ");

			checkTypeName(key_name);
		}

		//TODO: implement addNew(..., int/float/double/string/bool)
		template<class T>
		void addNew(const string& name, T& v)
		{
			if (checkIfNameExists(name)) FATAL_ERROR("Key " << name << " already exists ");

			VariableBase *new_var = new Variable<T>(v);

			new_var->name_ = name;
			new_var->str_type_name_ = typeid(v).name();
			
			vars_vec_.push_back(new_var);
		}

		template<class T>
		T& getVariable(const string& key_name)
		{
			checkTypeName<T>(key_name);

			Variable<T> *var = (Variable<T>*)findByName(key_name);

			return var->v_;
		}

		string getStrValue(const string& key_name)
		{
			return findByName(key_name)->getStrValue();
		}

		//void setValueFromStr(const string& key_name, const string& str_value)
		//{
		//	findByName(key_name)->setValueFromString(str_value);
		//}

		json getJson()
		{
			json category;
			json vars;

			for (const auto& itr : vars_vec_)
			{
				json attr;

				//attr["name"] = itr->name_;
				attr["type"] = itr->str_type_name_;
				attr["value"] = itr->getStrValue();

				vars[itr->name_] = attr;
			}

			category[name_] = vars;

			return category;
		}

		//TODO: getFloat, getDouble, getString, getBool
	};
}
