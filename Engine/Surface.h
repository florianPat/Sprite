#pragma once

#include "Colors.h"
#include <vector>
#include "Rect.h"

class Surface
{
	RectI rect;
	int width, height;
	Color* pixels = nullptr;
private:
	int leastSignificantSetBit(int bitfield);
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const std::string& filename, const RectI& rect);
	Surface(int width, int height, const RectI& rect);
	Surface(const Surface& other);
	Surface& operator=(const Surface& other);
	~Surface();
	RectI& getRect() const;
	void setRect(const RectI& newRect);
	int getWidth() const;
	int getHeight() const;
	Color getPixel(int x, int y) const;
	void putPixel(int x, int y, const Color& color);
};