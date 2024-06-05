#include "AssetManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <engine/D3DObjects/ImageTexture.h>

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::Instance()
{
	if (instance == nullptr)
	{
		return instance = new AssetManager();
	}
	return instance;
}

ImageTexture* AssetManager::getTexture(const std::string& imagePath)
{
	ImageTexture* image = textureMap[imagePath];
	if (!image)
	{
		image = textureMap[imagePath] = new ImageTexture(loadImageData(imagePath));
		loadedTextures.push_back(imagePath);
	}

	return image;
}


AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto it = loadedTextures.begin(); it != loadedTextures.end(); it++)
	{
		delete textureMap[*it];
	}
}

ImageData* AssetManager::loadImageData(const std::string& imagePath)
{
	ImageData* data = new ImageData;
	
	//Loaded images will always use 4 channels
	data->data = stbi_load(imagePath.c_str(), &data->width, &data->height, nullptr, 4);

	return data;
}
