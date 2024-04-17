﻿#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib") //visual studio
using namespace std;

#define SERVER_HOST "127.0.0.1"
#define SERVER_PORT 1234
#define INFO_SIZE 64
#define ADRESS 0

struct Student {
    char surname[50];
    int grades[4];
};

struct CommandResult {
    int messageNumber;
    int result;
};

bool find_grade(int* a, int x) {
    for (int i = 0; i < 4; i++) {
        if (a[i] == x) {
            return true;
        }
    }
    return false;
}

int sum_grade(int* a) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += a[i];
    }
    return sum;
}

int resultGeneration(Student student) {
    if (!find_grade(student.grades, 2)) {
        if (!find_grade(student.grades, 3)) {
            if (sum_grade(student.grades) == 20) {
                return 5;
            }
            else {
                return 4;
            }
        }
        else {
            return 3;
        }
    }
    else {
        return 2;
    }
}

int main() {
    /*char wsaData[1024];*/
    WSADATA wsaData;
    if (WSAStartup(0x0202, &wsaData)) {
        cerr << "Error WSAStartup: \n" << WSAGetLastError();
        return -1;
    }

    hostent* phostent;
    SOCKET sock;
    sockaddr_in sinServer, sinClient;
    int lenReceived;
    char infoReceived[INFO_SIZE] = { 0 };

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sinServer.sin_family = AF_INET;
    sinServer.sin_port = htons(SERVER_PORT);
    sinServer.sin_addr.s_addr = inet_addr(SERVER_HOST);
    if (inet_addr(SERVER_HOST)) {  //получили IPадрес
        sinServer.sin_addr.s_addr = inet_addr(SERVER_HOST);
    } else
        sinServer.sin_addr.s_addr = ((unsigned long**)phostent->h_addr_list)[0][0];
    }
    string stringSend, stringReceived;

    while (true) {
        int counterMessage = 0;
        boolean commandFlag = false;
        lenReceived = sizeof(sinClient);

        cout << "New connected client!" << endl;
        stringSend = "Hello, this is message from Server!";
        while (true) {
            counterMessage++;
            if (commandFlag == false) {
                sendto(sockNew, (char*)&stringSend[0], stringSend.size(), 0);

                fill(infoReceived, infoReceived + sizeof(infoReceived), 0);
                lenReceived = recv(sock, (char*)infoReceived, INFO_SIZE, 0);
                stringReceived = infoReceived;
                cout << "Client: " << stringReceived << endl;
                if (stringReceived == "Bye") {
                    break;
                }
                if (stringReceived == "/calcSchol") {
                    cout << "Waiting for the data..." << endl;
                    commandFlag = true;
                }
                else {
                    cout << "You: ";
                    getline(cin, stringSend);
                }
            }
            else {
                stringSend = "Enter the student's data.";
                send(sockNew, (char*)&stringSend[0], stringSend.size(), 0);

                Student studentReceived;
                lenReceived = recv(sockNew, (char*)&studentReceived, sizeof(Student), 0);

                CommandResult comRes;
                comRes.messageNumber = counterMessage;
                comRes.result = resultGeneration(studentReceived);
                send(sockNew, (char*)&comRes, sizeof(comRes), 0);

                commandFlag = false;
                cout << "The information has been processed" << endl;
                cout << "You: ";
                getline(cin, stringSend);
            }

        }
        cout << "client is lost";
    }
}
