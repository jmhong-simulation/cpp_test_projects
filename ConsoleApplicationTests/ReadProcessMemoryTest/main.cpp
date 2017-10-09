#include <iostream>
#include <string>
#include <Windows.h>
#include "..\PointerStringConverter.h"
#include "..\ProcessMemoryReadWrite.h"

/*
 
 https://www.youtube.com/watch?v=Vtlc-WP7iDw 
 http://www.cplusplus.com/forum/beginner/166135/

*/

using namespace std;

int cstyle_main();

int main()
{
	cstyle_main();

	cout << "--------------" << endl;
	cout << "Cpp style test" << endl;

	const string data_str("Read me, if you can!");

	ProcessMemoryReadWrite pm;
	pm.initialize(GetCurrentProcessId());
	cout << pm.read(data_str.c_str(), data_str.size()) << endl;

	pm.write(data_str.c_str(), "12345", 5);

	cout << data_str << endl;
}

int cstyle_main()
{
	PointerStringConverter conv;

	const char data_to_read [] = "Hello, memory hacking!";

	DWORD process_id = GetCurrentProcessId();
	cout << process_id << endl;

	// process id to string conversion test
	auto process_id_str = conv.value_to_string(process_id);
	DWORD process_id_after = conv.string_to_value<DWORD>(process_id_str);
	cout << process_id_after << " match " << (process_id == process_id_after) << endl;

	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);
	
	cout << pHandle << endl;

	if (pHandle == NULL) {
		cout << "Null handle " << endl;
	}

	LPVOID lpMem = (void*)&data_to_read;
	SIZE_T totalRead;
	totalRead = sizeof(data_to_read);

	SIZE_T data_size = sizeof(data_to_read);

	cout << "total read " << totalRead << endl;

	char buf[1024];
	ReadProcessMemory(pHandle, lpMem, (LPVOID)(&buf), data_size, &totalRead);

	cout << buf << " should be identical to " << data_to_read << endl;

	char buf_w[1024] = "123456789";
	SIZE_T size_to_write = 5; // 5 is just a simple test number
	SIZE_T size_written = 0;
	WriteProcessMemory(pHandle, lpMem, (LPVOID)(&buf_w), size_to_write, &size_written);

	cout << data_to_read << endl;

	CloseHandle(pHandle);

	return 0;
}