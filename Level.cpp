#include "Level.h"


Level::Level(void)
{

}


Level::~Level(void)
{
}

void Level::initializeFromXML(char* p_fileName)
{
	std::cout << "hahahaaha" << std::endl;
	std::string fileName = Settings::getString("XML_PATH")+p_fileName;
	std::cout << "FILENAME: " << fileName << std::endl;
	
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	pugi::xml_node root = doc.child("Level");
	pugi::xml_node staticActors = root.child("staticActors");
	for (pugi::xml_node staticActor = staticActors.child("staticActor"); staticActor; staticActor = staticActor.next_sibling("staticActor"))
	{
		std::string name = staticActor.attribute("name").value();
		StaticActorPtr staty = ActorManager::getNewStaticActor(name);
		if ( staticActor.child("position").empty() == 0 )
		{
			std::stringstream x_sstr;
			float x;
			x_sstr<<staticActor.child("position").attribute("x").value();
			x_sstr>>x;
			std::stringstream y_sstr;
			float y;
			y_sstr<<staticActor.child("position").attribute("y").value();
			y_sstr>>y;

			staty->setPosition(x,y);
		}
	}
}
