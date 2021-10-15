#pragma once
#include <string>

class Image
{
public:
	bool Load(const std::string& filename, uint8_t alpha = 255);

private:
	uint8_t* buffer{ 0 };
	int width{ 0 };
	int height{ 0 };
};