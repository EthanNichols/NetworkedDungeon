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

	int16_t Send(const IPAddress& ipAddress, const void* data, uint16_t size);
	int16_t Receive(void* data, uint16_t size, IPAddress* senderIP);

private:

	uint32_t socketID;
};

