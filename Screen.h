#pragma once
#include <map>
#include <vector>
#include "AbstractActor.h"
#include "Settings.h"
#include "libs/pugixml/pugixml.hpp"
#include <iostream>
#include "ActorManager.h"
#include "Polygon.h"
#include "EventManagerImpl.h"

class Screen : public IEventListener
{
public:
	Screen(void);
	~Screen(void);

	void initializeFromXML(char* p_fileName);

	bool VprocessEvent(EventPtr p_event);

private:
	std::vector<ActorPtr> m_staticActors;
	std::vector<ActorPtr> m_interactiveActors;

	std::vector<PolygonPtr> m_pathPolygons;

	std::map<std::string,bool> m_neededActors;

	bool m_isReady;
	pugi::xml_node m_root;
};

