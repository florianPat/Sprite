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
		assert(line == "<sounds>");

		assetFile.seekg(fileHeader.offsetToData);
		std::getline(assetFile, line);
		assert(line == "<data>");

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

Surface AssetLoader::LoadSurfaceFromASA(const std::string & filename)
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
		Surface result(bmpHeader.metadata.width, bmpHeader.metadata.height);

		assetFile.seekg(bmpHeader.metadata.offsetToPixels);

		assetFile.read((char*)result.pixels, sizeof(Color) * result.width * result.height);

		return result;
	}
	else
	{
		std::cerr << "File " + filename << " was not found in asset-file\n";
		return Surface();
	}
}
