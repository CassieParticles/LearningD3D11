#pragma once

#include <string>
#include <unordered_map>

class ImageTexture;

struct ImageData
{
	~ImageData() 
	{
		delete[] data; 
	}
	int width{};
	int height{};
	unsigned char* data{};
};

class AssetManager
{
public:

	static AssetManager* Instance();

	ImageTexture* getTexture(const std::string& imagePath);
protected:
	static AssetManager* instance;

	AssetManager();
	~AssetManager();

	ImageData* loadImageData(const std::string& imagePath);

	std::unordered_map<std::string, ImageTexture*> textureMap;
	std::vector<std::string> loadedTextures;
};