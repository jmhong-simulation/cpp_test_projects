#include <Windows.h>
#include <iostream>
#include <string>

class ProcessMemoryReadWrite
{
public:
	HANDLE pHandle;

	void initialize(const DWORD& process_id)
	{
		using namespace std;

		pHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);

		if (pHandle == NULL) {
			cout << "Null handle " << endl;
		}
	}

	std::string read(const void* ptr, const SIZE_T& data_size)
	{
		using namespace std;

		const LPVOID lpMem = (void*)ptr;
		//char buf[1024]; // buffer should be larger than size

		std::string data_str;
		data_str.resize(data_size);

		SIZE_T totalRead;
		ReadProcessMemory(pHandle, lpMem, (LPVOID)data_str.c_str(), data_size, &totalRead);
		
		cout << data_size << " " << totalRead << endl;
		//TODO: check totalRead

		return data_str;
	}

	void write(const void* ptr, const std::string& data_str_to_write, const SIZE_T& data_size_to_write)
	{
		using namespace std;

		const LPVOID lpMem = (void*)ptr;

		SIZE_T size_written = 0;
		WriteProcessMemory(pHandle, lpMem, (LPVOID)data_str_to_write.c_str(), data_size_to_write, &size_written);

		cout << data_size_to_write << " " << size_written << endl;
	}
};