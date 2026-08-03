
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

    ADDRINFO* addr_result_ptr = nullptr; // Необходимо удалять?
    result = getaddrinfo("localhost", "555", &hints, &addr_result_ptr);
    
    if (result !=0)
    {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }
    
    SOCKET connect_socket = INVALID_SOCKET;
    connect_socket = socket(addr_result_ptr->ai_family, addr_result_ptr->ai_socktype, addr_result_ptr->ai_protocol);

    if (connect_socket == INVALID_SOCKET)
    {
        cout << "Socket creation filed: " << endl;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    result = connect(connect_socket, addr_result_ptr->ai_addr, (int)addr_result_ptr->ai_addrlen);

    if (result == SOCKET_ERROR)
    {
        cout << "Unable connect to server: " << endl;
        closesocket(connect_socket);
        connect_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }


    const char* send_buffer = "Hello from client!";
    result = send(connect_socket, send_buffer, (int)strlen(send_buffer), 0);
    if (result == SOCKET_ERROR)
    {
        cout << "sent faled, error: " << result << endl;
        closesocket(connect_socket);
        connect_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    cout << "Sent:" << result << "bytes" << endl;

    result = shutdown(connect_socket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        cout << "Shutdown error:" << result << endl;
        closesocket(connect_socket);
        connect_socket = INVALID_SOCKET;
        freeaddrinfo(addr_result_ptr);
        WSACleanup();
        return 1;
    }

    char recv_buffet[512];

    do
    {
        ZeroMemory(recv_buffet, sizeof(recv_buffet));
        result = recv(connect_socket, recv_buffet, sizeof(recv_buffet), 0);
        if (result > 0)
        {
            cout << "Received:" << result << " bytes." << endl;
            cout << "Message data: " << recv_buffet << endl;
        }
        else if (result == 0)
        {
            cout << "connection closed" << endl;
        }
        else
        {
            cout << "recv failed with error" << endl;
        }
    } while (result > 0);

    closesocket(connect_socket);
    connect_socket = INVALID_SOCKET;
    freeaddrinfo(addr_result_ptr);
    WSACleanup();
    return 0;
}