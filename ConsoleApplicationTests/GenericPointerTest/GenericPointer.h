#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include "nlohmann\json.hpp"

namespace binding
{

#define FATAL_ERROR(message) {cout << __FUNCTION__ << endl; cout << message << endl; assert(false); exit(1);}

	using namespace std;
	using namespace nlohmann;

	class GenericPointer
	{
	private:
		string	name_ = "";
		string  type_ = "";
		void	*void_ptr_ = nullptr;

	public:
		template<class T>
		GenericPointer(const string& _var_name, T& _var)
			: name_(_var_name), type_(typeid(T).name()), void_ptr_((void*)&_var)
		{}

		GenericPointer(const json& js)
		{
			name_ = js["name"].get<string>();
			type_ = js["type"].get<string>();
			void_ptr_ = address_string_to_void_ptr(js["address"].get<string>());
		}

		template<class T>
		T* getPtr()
		{
			assertType<T>();

			return (T*)void_ptr_;
		}

		template<class T>
		T& getRef()
		{
			assertType<T>();

			return *getPtr<T>();
		}

		template<class T>
		void assertType() const
		{
			if (typeid(T).name() != type_) FATAL_ERROR("Type doesn't match " << typeid(T).name() << " " << type_);
		}

		template<class T>
		bool isType() const
		{
			if (typeid(T).name() == type_) return true;
			else return false;
		}

		string getStringValue() const
		{
			if (isType<int>())			return void_ptr_to_value_string<int>(void_ptr_);
			else if (isType<float>())	return void_ptr_to_value_string<float>(void_ptr_);
			else if (isType<bool>())	return void_ptr_to_value_string<bool>(void_ptr_);
			else if (isType<double>())	return void_ptr_to_value_string<double>(void_ptr_);
			else if (isType<string>())	return void_ptr_to_value_string<string>(void_ptr_);
			else FATAL_ERROR("Operation for this type is not defined " << type_);
		}

		void setValueByString(const string& str_value)
		{
			if (isType<int>())			getRef<int>()	 = stoi(str_value);
			else if (isType<float>())	getRef<float>()	 = stof(str_value);
			else if (isType<bool>())	getRef<bool>()	 = str_to_bool(str_value);
			else if (isType<double>())	getRef<double>() = stod(str_value);
			else if (isType<string>())	getRef<string>() = str_value;
			else FATAL_ERROR("Operation for this type is not defined " << type_);
		}

		json getJson()
		{
			json js;

			js["name"] = this->name_;
			js["type"] = this->type_;
			js["address"] = void_ptr_to_address_string(void_ptr_);

			return js;
		}

	public: // helper functions
		template<class T>
		static string void_ptr_to_value_string(void *void_ptr)
		{
			const T *typed_ptr = (T*)void_ptr;

			stringstream ss;
			ss << *typed_ptr;

			return ss.str();
		}

		static bool str_to_bool(const string& str_value)
		{
			if (str_value != "0" || str_value == "true") return true;
			else return false;
		}

		static string void_ptr_to_address_string(void *void_ptr)
		{
			string address_str;
			address_str.resize(sizeof(void*));			// x64: 8, x86: 4
			sprintf(&address_str[0], (char*)&void_ptr);

			return address_str;
		}

		static void* address_string_to_void_ptr(const string& add_str)
		{
			void *void_ptr_back;
			sprintf((char*)&void_ptr_back, add_str.c_str());

			return void_ptr_back;
		}
	};
}