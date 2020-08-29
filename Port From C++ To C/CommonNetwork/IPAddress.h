#pragma once

#include <stdint.h>
#include <string>

/// <summary>
/// Helper class that makes handling IP addresses easier.
/// </summary>
class IPAddress
{
public:
	IPAddress();
	IPAddress(int a, int b, int c, int d, int port);
	IPAddress(int address, int port);
	~IPAddress();

	void SetAddress(int a, int b, int c, int d);
	void SetAddress(int address);
	void SetA(int a);
	void SetB(int b);
	void SetC(int c);
	void SetD(int d);
	void SetIPPort(int port);

	/// <summary>
	/// Get the IP address as an int of all the bit shifted adress values
	/// </summary>
	int GetAddress() const;
	/// <summary>
	/// Get the first value of the IP address
	/// </summary>
	int GetA() const;
	/// <summary>
	/// Get the second value of the IP address
	/// </summary>
	int GetB() const;
	/// <summary>
	/// Get the third value of the IP address
	/// </summary>
	int GetC() const;
	/// <summary>
	/// Get the forth value of the IP address
	/// </summary>
	int GetD() const;
	/// <summary>
	/// Get the port of the IP address
	/// </summary>
	int GetPort() const;

	/// <summary>
	/// Get the string version of an IP address without the port
	/// </summary>
	std::string ToString() const;

	/// <summary>
	/// Compare if the IP address and port match another IPAddress
	/// </summary>
	int operator==(IPAddress rhs);

private:
	int address;
	int port;
};

// Include inline functions file
#include "IPAddress.inl"