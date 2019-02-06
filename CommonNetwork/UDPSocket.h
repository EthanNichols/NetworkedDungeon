#pragma once

#include "IPAddress.h"
#include <stdint.h>

class UDPSocket
{
public:

	UDPSocket();
	~UDPSocket();

	bool Open(const IPAddress& ipAddress);
	bool IsOpen() const;
	void Close();
	void BlockProgram(bool block);

	int Send(const IPAddress& ipAddress, const void* data, int size);
	int Receive(void* data, int size, IPAddress* senderIP);

private:

	int socketID;
};

