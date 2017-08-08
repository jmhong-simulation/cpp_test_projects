#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <string>
#include <iostream>
#include "PointerStringConverter.h"

using namespace std;

class IPCServer
{
public:

	SOCKET server_socket;
	SOCKET client_socket;

	IPCServer()
	{}

	~IPCServer()
	{
		closesocket(client_socket);
		WSACleanup();
	}

	void initialize(const int& port)
	{
		// Initialize Winsock 2.2
		WSADATA wsa_data;
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		{
			printf("WSAStartup() error! \n");
		}

		// Initialize server socker 
		server_socket = socket(PF_INET, SOCK_STREAM, 0);
		if (server_socket == INVALID_SOCKET)
		{
			printf("socket() error\n");
		}

		SOCKADDR_IN server_address;
		memset(&server_address, 0, sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		server_address.sin_port = htons(port);

		// Bind server socket and server address
		if (bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
		{
			printf("bind() error\n");
		}
	}

	void listen_and_accept()
	{
		// Wait for (listen) connection from client
		if (listen(server_socket, 5) == SOCKET_ERROR)
		{
			printf("listen() error\n");
		}

		printf("Waiting for client connection\n");

		// Accept connection from client
		SOCKADDR_IN client_address;
		int size_client_address = sizeof(client_address);
		client_socket = accept(server_socket, (SOCKADDR*)&client_address, &size_client_address);
		if (client_socket == INVALID_SOCKET)
		{
			printf("accept() error\n");
		}
	}

	void sendMessage(const std::string& message)
	{
		// Send data to client
		/*char message_buffer[1024];
		strcpy(message_buffer, "Hello from server!");
		send(client_socket, message_buffer, sizeof(message_buffer), 0);*/

		/*char message_buffer[1024];
		strcpy(message_buffer, "Hello from server!");*/

		cout << "Server send message size " << message.size() << endl;

		send(client_socket, message.c_str(), message.size(), 0);
	}

	std::string receiveMessage()
	{
		// Receive data from client
		char message_buffer[1024];
		int strLen = recv(client_socket, message_buffer, sizeof(message_buffer), 0);
		
		if (strLen == -1)
		{
			printf("read() error");
		}

		return std::string(message_buffer);

		/*message_buffer[strLen] = '\0';
		printf("Message from client : %s \n", message_buffer);*/
	}
};

int main(int argc, char **argv)
{
	// Print usage if arguments were not properly defined.
	if (argc != 2)
	{
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	IPCServer server;
	server.initialize(atoi(argv[1]));
	server.listen_and_accept();
	
	server.sendMessage("String message from server!");
	cout << server.receiveMessage() << endl;

	int variable_in_server = 1234;

	cout << "Ptr in server " << &variable_in_server << endl;

	const string ptr_str = PointerStringConverter::pointer_to_string(&variable_in_server);
	server.sendMessage(ptr_str);

	cout << server.receiveMessage() << endl;

	cout << variable_in_server << endl;


	return 0;
}
