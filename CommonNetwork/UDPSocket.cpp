#include "UDPSocket.h"
#include <winsock.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

UDPSocket::UDPSocket()
{
	socketID = static_cast<uint32_t>(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
}

UDPSocket::~UDPSocket()
{
	closesocket(socketID);
}

bool UDPSocket::Open(const IPAddress& ipAddress)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(ipAddress.GetPort());
	inet_pton(AF_INET, ipAddress.ToString().c_str(), &address.sin_addr);

	return bind(socketID, (const sockaddr*)&address, sizeof(sockaddr_in)) != SOCKET_ERROR;
}

bool UDPSocket::IsOpen() const
{
	char errorID;
	int errorSize = sizeof(errorID);
	getsockopt(socketID, SOL_SOCKET, SO_ACCEPTCONN, &errorID, &errorSize);

	return errorID;
}

void UDPSocket::Close()
{
	closesocket(socketID);
}

void UDPSocket::BlockProgram(bool block)
{
	u_long blockI = !block;
	int error = ioctlsocket(socketID, FIONBIO, &blockI);
}

int16_t UDPSocket::Send(const IPAddress& ipAddress, const void* data, uint16_t size)
{
	sockaddr_in sendHints;
	sendHints.sin_family = AF_INET;
	sendHints.sin_port = htons(ipAddress.GetPort());
	inet_pton(AF_INET, ipAddress.ToString().c_str(), &sendHints.sin_addr);

	return sendto(socketID, reinterpret_cast<const char*>(data), size, 0, (sockaddr*)&sendHints, sizeof(sendHints));
}

int16_t UDPSocket::Receive(void* data, uint16_t size, IPAddress* senderIP)
{
	sockaddr_in sender;
	int senderSize = sizeof(sender);

	int16_t recvStatus = recvfrom(socketID, reinterpret_cast<char*>(data), size, 0, (sockaddr*)&sender, &senderSize);

	if (senderIP != NULL)
	{
		inet_ntop(AF_INET, &sender.sin_addr, NULL, NULL);
		senderIP->SetAddress(static_cast<uint32_t>(ntohl(sender.sin_addr.S_un.S_addr)));
		senderIP->SetIPPort(static_cast<uint16_t>(ntohs(sender.sin_port)));
	}
	return recvStatus;
}
