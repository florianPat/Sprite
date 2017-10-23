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
	int offsetToBitmaps, offsetToSounds, offsetToData;
	int nBitmaps, nSounds;
};

struct BitmapHeader
{
	struct BitmapHeaderWOString
	{
		int width, height, pitch, bitsPerPixel;
		int offsetToPixels;
	} metadata;
	std::string filename;
	BitmapHeader() = default;
	BitmapHeader(const std::string& filename) : filename(filename) {};
};

//TODO: Implement Sound!!!

struct SoundHeader
{
	struct SoundHeaderWOString
	{
		//TODO: Implement this!
		int x;
	} metadata;
	std::string filename;
	SoundHeader() = default;
	SoundHeader(const std::string& filename) : filename(filename) {};
};
//TODO: Implement Sound!!!
class Sound
{

};

#pragma pack(pop)