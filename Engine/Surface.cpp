#include "Surface.h"
#include <assert.h>

Surface::Surface(const std::string & filename)
{
}

Surface::Surface(int width, int height) : width(width), height(height), pixels(new Color[width * height])
{
}

Surface::Surface(const Surface & other) : width(other.width), height(other.height), pixels(new Color[width * height])
{
	int nPixels = width * height;
	for (int i = 0; i < nPixels; ++i)
	{
		pixels[i] = other.pixels[i];
	}
}

Surface & Surface::operator=(const Surface & other)
{
	delete[] pixels;
	pixels = nullptr;

	width = other.width;
	height = other.height;

	pixels = new Color[width * height];

	int nPixels = width * height;
	for (int i = 0; i < nPixels; ++i)
	{
		pixels[i] = other.pixels[i];
	}

	return *this;
}

Surface::~Surface()
{
	delete[] pixels;
	pixels = nullptr;
}

int Surface::getWidth() const
{
	return width;
}

int Surface::getHeight() const
{
	return height;
}

Color Surface::getPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pixels[x + y * width];
}

void Surface::setPixel(int x, int y, const Color & color)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pixels[x + y * width] = color;
}
