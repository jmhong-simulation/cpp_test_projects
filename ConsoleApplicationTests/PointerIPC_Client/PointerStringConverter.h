#include <string>

class PointerStringConverter
{
public:
	template<class T>
	static std::string pointer_to_string(const T* variable)
	{
		using namespace std;

		// cast to void pointer
		void *ptr_var = (void*)variable;

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