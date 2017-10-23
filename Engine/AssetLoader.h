#pragma once

#include "AssetStructs.h"
#include "Surface.h"

class AssetLoader
{
	std::ifstream assetFile;
	int offsetToBitmaps, offsetToSounds;
	int nBitmaps, nSounds;
	std::vector<Surface> loadedSurfaces;
public:
	AssetLoader();
	~AssetLoader();
	AssetLoader(const AssetLoader& al) = delete;
	AssetLoader& operator=(const AssetLoader& al) = delete;
	//Check with operator bool if its "correct"
	Surface LoadSurfaceFromASA(const std::string& filename);
};