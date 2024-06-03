#include "AssetManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::Instance()
{
	if (instance == nullptr)
	{
		return instance = new AssetManager();
	}
	return instance;
}

ImageData* AssetManager::getImage(const std::string& imagePath)
{
	ImageData* image = imageMap[imagePath];

	//Image hasn't been loaded before
	if (!image)
	{
		image = imageMap[imagePath] = loadImage(imagePath);
	}

	return image;
}

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

ImageData* AssetManager::loadImage(const std::string& imagePath)
{
	ImageData* data = new ImageData;
	
	//Loaded images will always use 4 channels
	data->data = stbi_load(imagePath.c_str(), &data->width, &data->height, nullptr, 4);

	return data;
}
