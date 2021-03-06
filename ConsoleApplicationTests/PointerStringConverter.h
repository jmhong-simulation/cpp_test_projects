#include <string>

class PointerStringConverter
{
public:
	template<class T>
	static std::string value_to_string(const T& value)
	{
		using namespace std;

		void *ptr_var = (void*)&value;

		string str;
		str.resize(sizeof(T));
		memcpy((void*)str.c_str(), ptr_var, sizeof(T));
		//sprintf(&str[0], (char*)&ptr_var);

		return str;
	}

	template<class T>
	static T string_to_value(const std::string& str)
	{
		using namespace std;

		T value;

		memcpy((void*)&value, (void*)str.c_str(), sizeof(T));

		//sprintf((char*)&value, str.c_str());

		// cast void pointer to int pointer again
		return value;
	}

	template<class T>
	static std::string pointer_to_string(const T* var_ptr)
	{
		using namespace std;

		// cast to void pointer
		void *ptr_var = (void*)var_ptr;

		// save void pointer as string
		string ptr_str;
		ptr_str.resize(sizeof(void*));
		sprintf(&ptr_str[0], (char*)&ptr_var);

		return ptr_str;
	}

	template<class T>
	static T* string_to_pointer(const std::string& ptr_str)
	{
		using namespace std;

		void *ptr_back = nullptr;
		sprintf((char*)&ptr_back, ptr_str.c_str());

		// cast void pointer to int pointer again
		return (T*)ptr_back;
	}
};