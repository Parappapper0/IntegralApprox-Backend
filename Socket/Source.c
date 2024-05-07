#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 8192

int main() {

	int z = 0;
	printf("%d", 3 / z);


	WSADATA wsa_data;
	int result;
	result = WSAStartup(MAKEWORD(2, 2), &wsa_data);

	if (result != 0) {

		printf("C'%c stato un errore nello WSAStartup : %d\n", (char)138, result);
		return 1;
	}

	struct addrinfo* s_result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	result = getaddrinfo(NULL, "80", &hints, &s_result);
	if (result != 0) {
		printf("C'%c stato un errore nel getaddrinfo : %d\n", (char)138, result);
		WSACleanup();
		return 1;
	}

	SOCKET server_socket = INVALID_SOCKET;
	server_socket = socket(s_result->ai_family, s_result->ai_socktype, s_result->ai_protocol);

	if (server_socket == INVALID_SOCKET) {
		printf("C'%c stato un errore nel socket() : %ld\n", (char)138, WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	result = bind(server_socket, s_result->ai_addr, (int)s_result->ai_addrlen);
	if (result == SOCKET_ERROR) {
		printf("C'%c stato un errore nel bind: %d\n", (char)138, WSAGetLastError());
		freeaddrinfo(result);
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(s_result);

	if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
		printf("C'%c stato un errore nel listen: %ld\n", (char)138, WSAGetLastError());
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}

	SOCKET client_socket;

	client_socket = INVALID_SOCKET;

	client_socket = accept(server_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		printf("C'%c stato un errore nell'accept: %d\n", (char)138, WSAGetLastError());
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}

	char recvbuf[DEFAULT_BUFLEN];
	int send_result;
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do {
		

		result = recv(client_socket, recvbuf, recvbuflen, 0);
		if (result > 0) {

			//show received data
			printf("Byte ricevuti: %d\n", result);
			printf("Contenuto ricevuto: \n%s", recvbuf);





			// Echo the buffer back to the sender
			send_result = send(client_socket, recvbuf, result, 0);
			if (send_result == SOCKET_ERROR) {
				printf("C'%c stato un errore nell'invio: %d\n", (char)138, WSAGetLastError());
				closesocket(client_socket);
				WSACleanup();
				return 1;
			}
			printf("Byte inviati: %d\n", send_result);
		}
		else if (result == 0)
			printf("Chiusura connessione...\n");
		else {
			printf("C'%c stato un errore nella ricezione: %d\n", (char)138, WSAGetLastError());
			closesocket(client_socket);
			WSACleanup();
			return 1;
		}

	} while (result > 0);

	system("pause");
	system("pause");
	system("pause");
	system("pause");
	system("pause");
	system("pause");
	system("pause");
	return 0;
}