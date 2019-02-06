#include "IPAddress.h"

IPAddress::IPAddress()
{
}

IPAddress::IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port)
{
	address = (a << 24) + (b << 16) + (c << 8) + d;
	this->port = port;
}

IPAddress::IPAddress(uint32_t address, uint16_t port)
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
