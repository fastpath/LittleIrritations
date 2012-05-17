#include <boost/container/map.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <iostream>
#include "Settings.h"

class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);

	static boost::shared_ptr<sf::Texture> getTexture(std::string fileName);

private:
	static boost::container::map<std::string,boost::shared_ptr<sf::Texture> > s_textures;
};

