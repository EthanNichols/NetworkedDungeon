#pragma once

#include <stdint.h>
#include <string>

class IPAddress
{
public:
	IPAddress();
	IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port);
	IPAddress(uint32_t address, uint16_t port);
	~IPAddress();

	void SetAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
	void SetAddress(uint32_t address);
	void SetA(uint8_t a);
	void SetB(uint8_t b);
	void SetC(uint8_t c);
	void SetD(uint8_t d);
	void SetIPPort(uint16_t port);

	uint32_t GetAddress() const;
	uint8_t GetA() const;
	uint8_t GetB() const;
	uint8_t GetC() const;
	uint8_t GetD() const;
	uint16_t GetPort() const;
	std::string ToString() const;

private:
	uint32_t address;
	uint16_t port;
};

#include "IPAddress.inl"