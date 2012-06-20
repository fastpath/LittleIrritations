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

		PropertyPtr actorType = PropertyPtr(new TProperty<ActorType>(ACTORTYPE,DRAWABLE_ACTOR));
		newEvent->addProperty(actorType);

		PropertyPtr actorName = PropertyPtr(new TProperty<std::string>(NAME,name));
		newEvent->addProperty(actorName);

		if ( staticActor.child("position").empty() == 0 )
		{
			Pose actorPose;
			pugi::xml_node xPosi = staticActor.child("position");
			
			std::stringstream x_sstr;
			float x;
			x_sstr << xPosi.attribute("x").value();
			x_sstr >> x;
			
			std::stringstream y_sstr;
			float y;
			y_sstr << xPosi.attribute("y").value();
			y_sstr >> y;
			
			std::stringstream z_sstr;
			float z;
			z_sstr << xPosi.attribute("z").value();
			z_sstr >> z;
			
			actorPose.setPosition(x,y,z);
			//staty->setPosition(x,y,z);
			PropertyPtr pose = PropertyPtr(new TProperty<Pose>(POSE,actorPose));
			newEvent->addProperty(pose);
		}
		IBaseEventManager::Get()->VQueueEvent(newEvent);
	}

	pugi::xml_node xPathPolygons = m_root.child("pathPolygons");
	for (pugi::xml_node xItPolygon = xPathPolygons.child("pathPolygon"); xItPolygon; xItPolygon = xItPolygon.next_sibling("pathPolygon"))
	{
		PolygonPtr pPathPolygon = PolygonPtr(new Polygon());
		int pointCount = 0;
		for (pugi::xml_node xItPoint = xItPolygon.child("point"); xItPoint; xItPoint = xItPoint.next_sibling("point"))
		{
			std::stringstream x_sstr;
			float x;
			x_sstr << xItPoint.attribute("x").value();
			x_sstr >> x;
			
			std::stringstream y_sstr;
			float y;
			y_sstr << xItPoint.attribute("y").value();
			y_sstr >> y;

			pPathPolygon->addPoint(x,y);
			//std::cout << "Add Point  (" << x << "," << y << ")" << std::endl;
		}
		m_pathPolygons.push_back(pPathPolygon);
	}

	pugi::xml_node xObstaclePolygons = m_root.child("obstaclePolygons");
	for (pugi::xml_node xItObsPolygon = xObstaclePolygons.child("obstaclePolygon"); xItObsPolygon; xItObsPolygon = xItObsPolygon.next_sibling("obstaclePolygon"))
	{
		PolygonPtr pObstaclePolygon = PolygonPtr(new Polygon());
		int pointCount = 0;
		for (pugi::xml_node xItPoint = xItObsPolygon.child("point"); xItPoint; xItPoint = xItPoint.next_sibling("point"))
		{
			std::stringstream x_sstr;
			float x;
			x_sstr << xItPoint.attribute("x").value();
			x_sstr >> x;
			
			std::stringstream y_sstr;
			float y;
			y_sstr << xItPoint.attribute("y").value();
			y_sstr >> y;

			pObstaclePolygon->addPoint(x,y);
			//std::cout << "Add Point  (" << x << "," << y << ")" << std::endl;
		}
		m_obstaclePolygons.push_back(pObstaclePolygon);
	}
}

bool Screen::isReady(void)
{
	return m_isReady;
}

void Screen::setReady(void)
{
	m_isReady = true;
}

PolygonPtr Screen::getPathPolygon(int p_index)
{
	return m_pathPolygons[p_index];
}

int Screen::getPathPolygonCount(void)
{
	return m_pathPolygons.size();
}

PolygonPtr Screen::getObstaclePolygon(int p_index)
{
	return m_obstaclePolygons[p_index];
}

int Screen::getObstaclePolygonCount(void)
{
	return m_obstaclePolygons.size();
}

void Screen::checkNewActor(EventPtr p_event)
{
	if (!m_isReady)
	{
		std::string newActorName;
		p_event->getProperty(newActorName,NAME);

		ActorPtr newActorPtr;
		p_event->getProperty(newActorPtr,ACTORPTR);

		int readyCount = m_neededActors.size();
		for (auto itNeededActors = m_neededActors.begin(); itNeededActors != m_neededActors.end(); ++itNeededActors)
		{
			bool value = (*itNeededActors).second;
			if (!value)
			{
				std::string name = (*itNeededActors).first;
				if (name.compare(newActorName) == 0)
				{
					m_screenActors[newActorPtr->getId()] = newActorPtr;
					value = true;
					(*itNeededActors).second = value;
				}
			}
			
			if(value == true)
			{
				readyCount--;
			}
		}
		std::cout << "readyCount ist " << readyCount << std::endl;
		if (readyCount == 0)
		{
			this->setReady();
		}
	}
}

bool Screen::VprocessEvent(EventPtr p_event)
{
	switch (p_event->GetEventType())
	{
		case NEW_ACTOR:
			{
				this->checkNewActor(p_event);
				std::cout << "New Actor to Screen" << std::endl;
			} break;
		default:
			break;
	}
	
	return true;
}
