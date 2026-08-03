
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

int main()
{
    WSADATA wsa_data;
    int result;
    result = WSAStartup(MAKEWORD(2, 2), &wsa_data);

    if (result != 0)
    {
        cout << "WSAStartup failed, result = " << result << endl;
        return 1;
    }

    ADDRINFO hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;    // сервер

    ADDRINFO* addr_result_ptr = nullptr; // Необходимо удалять?
    result = getaddrinfo(NULL, "555", &hints, &addr_result_ptr);

    if (result != 0)
    {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    SOCKET client_socket = INVALID_SOCKET;
    SOCKET listen_socket = INVALID_SOCKET;
    listen_socket = socket(addr_result_ptr->ai_family, addr_result_ptr->ai_socktype, addr_result_ptr->ai_protocol);

    if (listen_socket == INVALID_SOCKET)
    {
        cout << "Socket creation filed: " << endl;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    result = bind(listen_socket, addr_result_ptr->ai_addr, (int)addr_result_ptr->ai_addrlen);

    if (result == SOCKET_ERROR)
    {
        cout << "Binding socket failed: " << endl;
        closesocket(listen_socket);
        listen_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    result = listen(listen_socket, SOMAXCONN);

    if (result == SOCKET_ERROR)
    {
        cout << "Listening socket failed: " << endl;
        closesocket(listen_socket);
        listen_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    client_socket = accept(listen_socket, NULL, NULL);
    if (result == SOCKET_ERROR)
    {
        cout << "Accepting socket failed: " << endl;
        closesocket(client_socket);
        client_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    closesocket(listen_socket);

    const char* send_buffer = "Hello from server!";
    char recv_buffet[512];

    do
    {
        ZeroMemory(recv_buffet, sizeof(recv_buffet));
        result = recv(client_socket, recv_buffet, sizeof(recv_buffet), 0);
        if (result > 0)
        {
            cout << "Received:" << result << " bytes." << endl;
            cout << "Message data: " << recv_buffet << endl;

            result = send(client_socket, send_buffer, (int)strlen(send_buffer), 0);
            if (result == SOCKET_ERROR)
            {
                cout << "Field to send data back";
                closesocket(client_socket);
                client_socket = INVALID_SOCKET;
                freeaddrinfo(addr_result_ptr);
                WSACleanup();
                return 1;
            }
        }
        else if (result == 0)
        {
            cout << "connection closing..." << endl;
        }
        else
        {
            cout << "recv failed with error" << endl;
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            freeaddrinfo(addr_result_ptr);
            WSACleanup();
            return 1;
        }
    } while (result > 0);

    result = shutdown(client_socket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        cout << "Shutdown error:" << result << endl;
        closesocket(client_socket);
        client_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    closesocket(client_socket);
    client_socket = INVALID_SOCKET;
    freeaddrinfo(addr_result_ptr);
    WSACleanup();
    return 0;
}