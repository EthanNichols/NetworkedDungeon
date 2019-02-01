#pragma once

struct command
{
	unsigned char cmd;
	char payload[256];
};

struct status
{
	unsigned char status;
	char payload[256];
};