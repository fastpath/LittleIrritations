#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "AbstractActor.h"
#include "MovableActor.h"
#include "StaticActor.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include "libs\pugixml\pugixml.hpp"
#include "Settings.h"
#include "TextureLoader.h"

class ActorManager
{
public:
	ActorManager(void);
	ActorManager(boost::shared_ptr<sf::RenderWindow> p_app);
	~ActorManager(void);

	static MovableActorPtr getNewMovableActor(const std::string& p_actorName);
	static StaticActorPtr getNewStaticActor(const std::string& p_actorName);

	void update(float p_dt);

	static ActorManager* Get(void);

private:
	static std::map<ActorType,std::list<ActorPtr> > m_actorMap;
	static std::map<float,std::list<ActorPtr> > m_drawableActorMap;
	static boost::shared_ptr<sf::RenderWindow> m_app;
	static std::list<float> m_levels;
	static unsigned int m_globalId;

	static void addActor(ActorPtr p_actor);
};

