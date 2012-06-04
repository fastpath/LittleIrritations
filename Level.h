#pragma once
#include <map>
#include <vector>
#include "AbstractActor.h"
#include "Settings.h"
#include "libs/pugixml/pugixml.hpp"
#include <iostream>
#include "ActorManager.h"
#include "Polygon.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void initializeFromXML(char* p_fileName);


private:
	std::vector<ActorPtr> m_staticActors;
	std::vector<ActorPtr> m_interactiveActors;

	std::vector<PolygonPtr> m_pathPolygons;
};

