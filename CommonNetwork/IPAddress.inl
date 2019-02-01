#pragma once

#pragma region Set Functions

inline void IPAddress::SetAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	address = (a << 24) + (b << 16) + (c << 8) + d;
}

inline void IPAddress::SetAddress(uint32_t address)
{
	this->address = address;
}

inline void IPAddress::SetA(uint8_t val)
{
	address ^= GetA() << 24;
	address += val << 24;
}

inline void IPAddress::SetB(uint8_t val)
{
	address ^= GetB() << 24;
	address += val << 24;
}

inline void IPAddress::SetC(uint8_t val)
{
	address ^= GetC() << 24;
	address += val << 24;
}

inline void IPAddress::SetD(uint8_t val)
{
	address ^= GetD() << 24;
	address += val << 24;
}

inline void IPAddress::SetIPPort(uint16_t port)
{
	this->port = port;
}

#pragma endregion

#pragma region Get Functions

inline uint32_t IPAddress::GetAddress() const
{
	return address;
}

inline uint8_t IPAddress::GetA() const
{
	uint32_t mask = 0xFF << 24;
	return (address & mask) >> 24;
}

inline uint8_t IPAddress::GetB() const
{
	uint32_t mask = 0xFF << 16;
	return (address & mask) >> 16;
}

inline uint8_t IPAddress::GetC() const
{
	uint32_t mask = 0xFF << 8;
	return (address & mask) >> 8;
}

inline uint8_t IPAddress::GetD() const
{
	uint32_t mask = 0xFF;
	return address & mask;
}

inline uint16_t IPAddress::GetPort() const
{
	return port;
}

#pragma endregion