#ifndef network_h
#define network_h

#include <stdint.h>
#include "model.h"

#define UDP_BUF_SIZE 888

int udpSetup(unsigned short inUdpPort, const char* inUdpAddr, ModelInstance *comp);
void udpTerminate(void);

void udpSend(char* sendData, const int sizeOfInputData, unsigned short outUdpPort, const char* outUdpAddr);
bool udpReceive(char* recvData, ModelInstance *comp);

#endif /* network_h */