#pragma once

#include <assert.h>
#include <fstream>
#include <Windows.h>
#include "Colors.h"
#include <vector>
#include <string>
#include <iostream>

#pragma pack(push, 1)
struct FileHeader
{
	int magicValue;
	int version;
	int offsetToBitmaps, offsetToSounds;
	int nBitmaps, nSounds;
};

struct BitmapHeader
{
	std::string filename;
	struct Metadata
	{
		int width, height, pitch, bitsPerPixel;
		int offsetToPixels;
	} metadata;
};

//TODO: Implement Sound!!!

struct SoundHeader
{
	std::string filename;
};

class Sound
{

};

#pragma pack(pop)