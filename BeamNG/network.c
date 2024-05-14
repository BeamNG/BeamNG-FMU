#include "network.h"

#include <stdbool.h>
#include <stdio.h>

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#elif __linux__
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

static bool connectionStarted = false;
static struct timeval tv;

#ifdef _WIN32
static SOCKET udpSocket;

static int windowsSocketSetup(u_short inUdpPort, const char *inUdpAddr, ModelInstance *comp) {
    // this function is called a the beginning of the simulation
    WSADATA wsaData;
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (res != NO_ERROR) {
        logError(comp, "WSAStartup failed with error ");
        return 1;
    }

    // Set up a socket to receive data from Lua, on port 64890.
    // and to send data to Lua, on port 64891.
    udpSocket = INVALID_SOCKET;
    udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == INVALID_SOCKET) {
        logError(comp, "UDP in socket failed with error %d", WSAGetLastError());
        return 1;
    }

    tv.tv_sec = 5000;  // milliseconds
    tv.tv_usec = 0;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
        logError(comp, "Error setting socket timeout");
    }
    if (setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&(BOOL){1}, sizeof(BOOL)) < 0) {
        logError(comp, "Error setting socket reuseaddr");
    }

    struct sockaddr_in serverAddrIn;
    serverAddrIn.sin_family = AF_INET;
    serverAddrIn.sin_port = htons(inUdpPort);
    serverAddrIn.sin_addr.s_addr = inet_addr(inUdpAddr);
    if (bind(udpSocket, (SOCKADDR *)&serverAddrIn, sizeof(serverAddrIn))) {
        logError(comp, "bind failed with error %d\n", WSAGetLastError());
        return 1;
    }
    WSASetLastError(0);
    return 0;
}

static void windowsSend(char *sendData, const int sizeOfInputData, u_short outUdpPort, const char *outUdpAddr) {
    struct sockaddr_in serverAddrOut;
    serverAddrOut.sin_family = AF_INET;
    serverAddrOut.sin_port = htons(outUdpPort);
    serverAddrOut.sin_addr.s_addr = inet_addr(outUdpAddr);
    sendto(udpSocket, sendData, sizeOfInputData, 0, (SOCKADDR *)&serverAddrOut, sizeof(serverAddrOut));
}

static bool windowsReceive(char *recvData, ModelInstance *comp) {
    struct sockaddr_in incomingAddress;
    int incomingAddrSize = sizeof(incomingAddress);
    recvfrom(udpSocket, recvData, UDP_BUF_SIZE, 0, (SOCKADDR *)&incomingAddress, &incomingAddrSize);

    while (WSAGetLastError() == WSAETIMEDOUT) {
        if (connectionStarted) {
            // ssSetStopRequested(S, 1);
            logError(comp, "Simulation stopped due to disconnection");
            connectionStarted = false;
            return false;
        }
        recvfrom(udpSocket, recvData, UDP_BUF_SIZE, 0, (SOCKADDR *)&incomingAddress, &incomingAddrSize);
    }

    if (!connectionStarted) {
        tv.tv_sec = 3000;  // milliseconds
        if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
            logError(comp, "Error setting socket timeout");
            return false;
        }

        logEvent(comp, "Connection opened at time: %f", comp->time);
        connectionStarted = true;
    }

    return true;
}

#elif __linux__
static int udpSocket;

static int linuxSocketSetup(u_short inUdpPort, const char *inUdpAddr, ModelInstance *comp) {
    // Set up a socket to receive data from Lua, on port 64890.
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket < 0) {
        logError(comp, "UDP in socket failed");
        return 1;
    }

    tv.tv_sec = 0;
    tv.tv_usec = 5000;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
        logError(comp, "Error setting socket timeout");
        close(udpSocket);
        return 1;
    }

    struct sockaddr_in serverAddrIn;
    serverAddrIn.sin_family = AF_INET;
    serverAddrIn.sin_port = htons(inUdpPort);
    inet_pton(AF_INET, inUdpAddr, &(serverAddrIn.sin_addr));

    if (bind(udpSocket, (struct sockaddr *)&serverAddrIn, sizeof(serverAddrIn)) < 0) {
        logError(comp, "Bind failed");
        close(udpSocket);
        return 1;
    }

    return 0;
}

static bool linuxReceive(char *recvData, ModelInstance *comp) {
    struct sockaddr_in incomingAddress;
    socklen_t incomingAddrSize = sizeof(incomingAddress);
    int recvLength = recvfrom(udpSocket, recvData, UDP_BUF_SIZE, 0, (struct sockaddr *)&incomingAddress, &incomingAddrSize);

    if (recvLength < 0) {
        if (connectionStarted) {
            logError(comp, "Simulation stopped due to disconnection");
            connectionStarted = false;
            return false;
        }
    } else {
        if (!connectionStarted) {
            tv.tv_sec = 3;
            tv.tv_usec = 0;
            if (setsockopt(udpSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
                printf("Error setting socket timeout");
                return false;
            }

            logEvent(comp, "Connection opened at time: %f", comp->time);
            connectionStarted = true;
        }
    }

    return true;
}

static void linuxSend(const char *sendData, const int sizeOfInputData, const u_short outUdpPort, const char *outUdpAddr) {
    struct sockaddr_in serverAddrOut;
    serverAddrOut.sin_family = AF_INET;
    serverAddrOut.sin_port = htons(outUdpPort);
    inet_pton(AF_INET, outUdpAddr, &serverAddrOut.sin_addr);
    sendto(udpSocket, sendData, sizeOfInputData, 0, (struct sockaddr *)&serverAddrOut, sizeof(serverAddrOut));
}
#endif

int udpSetup(unsigned short inUdpPort, const char *inUdpAddr, ModelInstance *comp) {
#ifdef _WIN32
    int status = windowsSocketSetup(inUdpPort, inUdpAddr, comp);
#elif __linux__
    int status = linuxSocketSetup(inUdpPort, inUdpAddr, comp);
#endif
    if (status == 0) {
        connectionStarted = false;
    }
    return status;
}

void udpSend(char *sendData, const int sizeOfInputData, unsigned short outUdpPort, const char *outUdpAddr) {
#ifdef _WIN32
    windowsSend(sendData, sizeOfInputData, outUdpPort, outUdpAddr);
#elif __linux__
    linuxSend(sendData, sizeOfInputData, outUdpPort, outUdpAddr);
#endif
}

bool udpReceive(char *recvData, ModelInstance *comp) {
#ifdef _WIN32
    return windowsReceive(recvData, comp);
#else
    return linuxReceive(recvData, comp);
#endif
}

void udpTerminate(void) {
// this function is called at the end of the simulation
#ifdef _WIN32
    closesocket(udpSocket);
    WSACleanup();
#elif __linux__
    close(udpSocket);
#endif
}