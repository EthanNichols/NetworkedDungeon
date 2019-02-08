#pragma once

#include "IPAddress.h"
#include <stdint.h>

class UDPSocket
{
public:

	UDPSocket();
	~UDPSocket();

	/// <summary>
	/// Open and bind a socket to recieve packets at an IPAddress
	/// </summary>
	/// <return>Whether the socket was opened successfully</return>
	bool Open(const IPAddress& ipAddress);

	/// <summary>
	/// Returns whether this socket is open or not
	/// </summary>
	bool IsOpen() const;

	/// <summary>
	/// Close the socket
	/// </summary>
	void Close();

	/// <summary>
	/// Set whether the program will stop and wait to recieve a UDP packet
	/// </summary>
	void BlockProgram(bool block);

	/// <summary>
	/// Send data to an IP with this socket
	/// </summary>
	/// <param name="ipAddress">The IPAddress the data is being sent to</param>
	/// <param name="data">The packet data that is being sent</param>
	/// <param name="data">The size of the packet that is being sent</param>
	/// <return>Whether data was sent or data failed to be sent</return>
	int Send(const IPAddress& ipAddress, const void* data, int size);
	
	/// <summary>
	/// Recieve data with this socket
	/// </summary>
	/// <param name="data">Pointer to data buffer to store packet data</param>
	/// <param name="size">Size of the 'data' buffer passed in</param>
	/// <param name="senderIP">IPAddress to store the sender's IP address in</param>
	/// <return>Whether data was recieved or data failed to be recieved</return>
	int Receive(void* data, int size, IPAddress* senderIP);

private:

	int socketID;
};

