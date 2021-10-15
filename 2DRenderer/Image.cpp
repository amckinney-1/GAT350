#include "Image.h"
#include "Renderer.h"
#include <fstream>
#include <iostream>

bool Image::Load(const std::string& filename, uint8_t alpha)
{
	std::ifstream stream(filename, std::ios::binary);
	if (stream.fail())
	{
		std::cout << "Error: Cannot open file: " << filename << std::endl;
		return false;
	}

	uint8_t header[54];
	stream.read((char*)header, 54);

	uint16_t id = *((uint16_t*)(header));
	if (id != 'MB')
	{
		std::cout << "Error: Invalid file format: " << filename << std::endl;
		return false;
	}

	width = *((int*)(&header[18]));
	height = *((int*)(&header[22]));

	int pitch = width * sizeof(color_t);
	buffer = new uint8_t[width * pitch];
	
	uint16_t bitsPerPixel = *((uint16_t*)(&header[28]));
	uint16_t bytesPerPixel = bitsPerPixel / 8;

	size_t size = width * height * bytesPerPixel;
	uint8_t* data = new uint8_t[size];

	//stream.read(header, size); // *************NOT CORRECT**************


}