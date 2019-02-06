#pragma once

#include <stdint.h>
#include <string>

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

	int GetAddress() const;
	int GetA() const;
	int GetB() const;
	int GetC() const;
	int GetD() const;
	int GetPort() const;
	std::string ToString() const;

	int operator==(IPAddress rhs);

private:
	int address;
	int port;
};

#include "IPAddress.inl"