#include "IPAddress.h"

IPAddress::IPAddress()
{
}

IPAddress::IPAddress(int a, int b, int c, int d, int port)
{
	address = (a << 24) + (b << 16) + (c << 8) + d;
	this->port = port;
}

IPAddress::IPAddress(int address, int port)
{
	this->address = address;
	this->port = port;
}

IPAddress::~IPAddress()
{
}

std::string IPAddress::ToString() const 
{
	std::string strOut;

	strOut.append(&std::to_string(GetA())[0]);
	strOut.append(".");
	strOut.append(&std::to_string(GetB())[0]);
	strOut.append(".");
	strOut.append(&std::to_string(GetC())[0]);
	strOut.append(".");
	strOut.append(&std::to_string(GetD())[0]);

	return strOut;
}

int IPAddress::operator==(IPAddress rhs)
{
	if (rhs.port == port &&
		rhs.address == address)
	{
		return 1;
	}

	return 0;
}
