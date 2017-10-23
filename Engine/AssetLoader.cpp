#include "AssetLoader.h"

AssetLoader::AssetLoader()
{
	assetFile.open("data.asa", std::ios::binary);

	if (assetFile)
	{
		FileHeader fileHeader = {};

		assetFile.read((char*)&fileHeader, sizeof(fileHeader));

		assert(fileHeader.magicValue == 'ASA');
		assert(fileHeader.version == 1);

		std::string line;
		std::getline(assetFile, line);
		assert(line == "<table>");

		std::getline(assetFile, line);
		assert(line == "<bitmaps>");

		assetFile.seekg(fileHeader.offsetToBitmaps);
		std::getline(assetFile, line);
		assert(line == "<bitmaps>");

		assetFile.seekg(fileHeader.offsetToSounds);
		std::getline(assetFile, line);
		//assert(line == "<sounds>");

		offsetToBitmaps = fileHeader.offsetToBitmaps;
		offsetToSounds = fileHeader.offsetToSounds;

		nBitmaps = fileHeader.nBitmaps;
		nSounds = fileHeader.nSounds;
	}
	else
		std::cerr << "Failed to open file!" << std::endl;
}

AssetLoader::~AssetLoader()
{
	assetFile.close();
}

Surface AssetLoader::LoadFromASA(const std::string & filename)
{
	BitmapHeader bmpHeader;
	bool found = false;

	std::string line;
	assetFile.seekg(offsetToBitmaps);
	std::getline(assetFile, line);
	assert(line == "<bitmaps>");

	for (int i = 0; i < nBitmaps; ++i)
	{
		char next = 0;
		bmpHeader.filename.clear();
		for(char next = assetFile.get(); next != '\0'; next = assetFile.get())
		{
			bmpHeader.filename.push_back(next);
		}
		assetFile.read((char*)&bmpHeader.metadata, sizeof(bmpHeader.metadata));
		if (bmpHeader.filename == filename)
		{
			found = true;
			break;
		}
	}

	if (found)
	{
		Surface result;

		result.width = bmpHeader.metadata.width;
		result.height = bmpHeader.metadata.height;

		result.pixels = new Color(result.width * result.height);
		assetFile.seekg(bmpHeader.metadata.offsetToPixels, std::ios::cur);

		for (int y = 0; y < result.height; ++y)
		{
			for (int x = 0; x < result.width; ++x)
			{
				Color color;
				assetFile.read((char*)&color, sizeof(Color));
				result.putPixel(x, y, color);
			}
		}

		result.rect = RectI(Vec2_<int>(0, 0), result.width, result.height);

		return result;
	}
	else
	{
		std::cerr << "File " + filename << " was not found in asset-file\n";
		return Surface();
	}
}
