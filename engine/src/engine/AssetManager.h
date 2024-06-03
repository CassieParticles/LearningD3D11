#pragma once

#include <string>
#include <unordered_map>

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

	ImageData* getImage(const std::string& imagePath);
protected:
	static AssetManager* instance;

	AssetManager();
	~AssetManager();

	ImageData* loadImage(const std::string& imagePath);

	std::unordered_map<std::string, ImageData*> imageMap;
};