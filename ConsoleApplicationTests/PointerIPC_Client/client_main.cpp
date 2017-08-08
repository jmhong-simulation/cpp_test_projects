#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include "..\PointerStringConverter.h"
#include "..\ProcessMemoryReadWrite.h"

using namespace std;

class IPCClient
{
public:
	SOCKET h_socket;

	~IPCClient()
	{
		// Close connection
		closesocket(h_socket);
		WSACleanup();
	}

	void initialize(const string& server_address_str, const int& port_number)
	{
		// Initialize WinSocket 2.2
		WSADATA wsa_data;
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		{
			printf("WSAStartup() error\n");
		}

		// Initialize socket
		h_socket = socket(PF_INET, SOCK_STREAM, 0);
		if (h_socket == INVALID_SOCKET)
		{
			printf("socket(), error\n");
		}

		// Initialize server address and port
		SOCKADDR_IN server_address;
		memset(&server_address, 0, sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = inet_addr(server_address_str.c_str());
		server_address.sin_port = htons(port_number);

		// Connect to server
		if (connect(h_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
		{
			printf("Connect() error\n");
		}
	}

	string receiveMessage()
	{
		// Receive data from server
		// Note that server is programmed to send hello message.
		char message_buffer[1024];
		int strLen = recv(h_socket, message_buffer, sizeof(message_buffer), 0);		

		cout << "Client receive message size " << strLen << endl;

		if (strLen == -1)
		{
			printf("read() error\n");
		}

		// Not to copy gabages at the end of message_buffer
		string message;
		message.resize(strLen);
		memcpy((void*)message.c_str(), message_buffer, strLen);

		return message;
	}

	void sendMessage(const string& message)
	{
		cout << "Client send message size " << message.size() << endl;

		send(h_socket, message.c_str(), message.size(), 0);
	}
};

int main(int argc, char **argv)
{
	// Print usage if arguments were not properly defined.
	if (argc != 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	IPCClient client;
	client.initialize(argv[1], atoi(argv[2]));
	string message = client.receiveMessage();
	cout << message << " size " << message.size() << endl;
	
	client.sendMessage("Message from client!*~");

	auto pid_str = client.receiveMessage();
	auto ptr_str = client.receiveMessage();

	PointerStringConverter conv;
	auto pid = conv.string_to_value<DWORD>(pid_str);
	cout << "Received pid " << pid << endl;

	auto ptr = conv.string_to_pointer<int>(ptr_str);
	cout << "Received ptr " << ptr << endl;

	ProcessMemoryReadWrite pm;
	pm.initialize(pid);

	std::string str_temp = pm.read((void*)ptr, sizeof(int)); // we know this is integer

	const int value_in_server = conv.string_to_value<int>(str_temp);

	cout << value_in_server << " This should be equal to the value in server" << endl;

	pm.write((void*)ptr, conv.value_to_string<int>(1024), sizeof(int));

	client.sendMessage("Dummy");

	// naive pointer communication doesn't work
	//const string strptr_from_server = client.receiveMessage();
	//int* ptr = nullptr;
	//ptr = PointerStringConverter::string_to_pointer<int>(strptr_from_server);

	//cout << "Check in client " << ptr << endl;
	//
	//try {
	//	cout << " " << *ptr << endl; // ERROR! don't know why!
	//}
	//catch (const char* msg)
	//{
	//	cout << msg << endl;
	//}


	//*ptr = 256;

	//client.sendMessage("dummy");

	return 0;
}
