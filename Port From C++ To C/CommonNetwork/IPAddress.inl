#pragma once

#pragma region Set Functions

inline void IPAddress::SetAddress(int a, int b, int c, int d)
{
	address = (a << 24) + (b << 16) + (c << 8) + d;
}

inline void IPAddress::SetAddress(int address)
{
	this->address = address;
}

inline void IPAddress::SetA(int val)
{
	address ^= GetA() << 24;
	address += val << 24;
}

inline void IPAddress::SetB(int val)
{
	address ^= GetB() << 24;
	address += val << 24;
}

inline void IPAddress::SetC(int val)
{
	address ^= GetC() << 24;
	address += val << 24;
}

inline void IPAddress::SetD(int val)
{
	address ^= GetD() << 24;
	address += val << 24;
}

inline void IPAddress::SetIPPort(int port)
{
	this->port = port;
}

#pragma endregion

#pragma region Get Functions

inline int IPAddress::GetAddress() const
{
	return address;
}

inline int IPAddress::GetA() const
{
	int mask = 0xFF << 24;
	return (address & mask) >> 24;
}

inline int IPAddress::GetB() const
{
	int mask = 0xFF << 16;
	return (address & mask) >> 16;
}

inline int IPAddress::GetC() const
{
	int mask = 0xFF << 8;
	return (address & mask) >> 8;
}

inline int IPAddress::GetD() const
{
	int mask = 0xFF;
	return address & mask;
}

inline int IPAddress::GetPort() const
{
	return port;
}

#pragma endregion