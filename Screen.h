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

	bool isReady(void);
	void setReady(void);

	bool VprocessEvent(EventPtr p_event);

	PolygonPtr getPathPolygon(int p_index);
	int getPathPolygonCount(void);
	PolygonPtr getObstaclePolygon(int p_index);
	int getObstaclePolygonCount(void);

	std::vector<PolygonPtr> m_pathPolygons;
	std::vector<PolygonPtr> m_obstaclePolygons;

private:
	std::vector<ActorPtr> m_staticActors;
	std::vector<ActorPtr> m_interactiveActors;



	std::map<std::string,bool> m_neededActors;
	std::map<int,ActorPtr> m_screenActors;

	void checkNewActor(EventPtr p_event);

	bool m_isReady;
	pugi::xml_node m_root;
};

