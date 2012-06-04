#include "TextureLoader.h"

std::map<std::string,boost::shared_ptr<sf::Texture> > TextureLoader::s_textures;

TextureLoader::TextureLoader(void)
{
}

TextureLoader::~TextureLoader(void)
{
}

boost::shared_ptr<sf::Texture> TextureLoader::getTexture(std::string fileName) {
	if (s_textures.find(fileName) != s_textures.end()) {
		return s_textures[fileName];
	} else {
		boost::shared_ptr<sf::Texture> newTexure(new sf::Texture);
		//std::cout << "Texture lesen aus: " << Settings::getString("TEXTURE_PATH") << std::endl;
		newTexure->loadFromFile(Settings::getString("TEXTURE_PATH")+fileName+".png");
		s_textures[fileName] = newTexure;
		return newTexure;
	}
}
