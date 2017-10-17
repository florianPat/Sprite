#pragma once

#include "Colors.h"
#include <vector>

class Surface
{
	int width, height;
	Color* pixels = nullptr;
private:
	int leastSignificantSetBit(int bitfield);
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface& other);
	Surface& operator=(const Surface& other);
	~Surface();
	int getWidth() const;
	int getHeight() const;
	Color getPixel(int x, int y) const;
	void putPixel(int x, int y, const Color& color);
};