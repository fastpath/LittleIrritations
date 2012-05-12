#include "TextureLoader.h"

boost::container::map<std::string,boost::shared_ptr<sf::Texture> > TextureLoader::s_textures;
std::string TextureLoader::s_textureFolder = "data/textures/";

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
		newTexure->loadFromFile(s_textureFolder+fileName+".png");
		s_textures[fileName] = newTexure;
		return newTexure;
	}
}
