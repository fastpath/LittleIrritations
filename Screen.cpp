#include "Screen.h"


Screen::Screen(void)
{
	m_isReady = false;
}


Screen::~Screen(void)
{
}

void Screen::initializeFromXML(char* p_fileName)
{
	std::cout << "hahahaaha" << std::endl;
	std::string fileName = Settings::getString("XML_PATH")+p_fileName;
	std::cout << "FILENAME: " << fileName << std::endl;
	
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	pugi::xml_node m_root = doc.child("Level");
	pugi::xml_node staticActors = m_root.child("staticActors");
	for (pugi::xml_node staticActor = staticActors.child("staticActor"); staticActor; staticActor = staticActor.next_sibling("staticActor"))
	{
		std::string name = staticActor.attribute("name").value();
		m_neededActors.insert(std::pair<std::string,bool>(name,false));

		EventPtr newEvent(new Event(CREATE_ACTOR,0.0f));

		PropertyPtr actorName = PropertyPtr(new TProperty<std::string>(NAME,name));
		newEvent->addProperty(actorName);

		if ( staticActor.child("position").empty() == 0 )
		{
			Pose actorPose;
			
			std::stringstream x_sstr;
			float x;
			x_sstr<<staticActor.child("position").attribute("x").value();
			x_sstr>>x;
			
			std::stringstream y_sstr;
			float y;
			y_sstr<<staticActor.child("position").attribute("y").value();
			y_sstr>>y;
			
			std::stringstream z_sstr;
			float z;
			z_sstr<<staticActor.child("position").attribute("z").value();
			z_sstr>>z;
			
			actorPose.setPosition(x,y,z);
			//staty->setPosition(x,y,z);
			PropertyPtr pose = PropertyPtr(new TProperty<Pose>(POSE,actorPose));
			newEvent->addProperty(pose);
		}

		IBaseEventManager::Get()->VQueueEvent(newEvent);
	}
}

bool Screen::VprocessEvent(EventPtr p_event)
{

	return true;
}
