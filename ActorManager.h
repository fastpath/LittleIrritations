#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "DrawableActor.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include "libs\pugixml\pugixml.hpp"
#include "Settings.h"
#include "IEventListener.h"
#include "TextureLoader.h"

class ActorManager : public IEventListener
{
public:
	ActorManager(void);
	ActorManager(boost::shared_ptr<sf::RenderWindow> p_app);
	~ActorManager(void);

	static DrawableActorPtr getNewDrawableActor(const std::string& p_actorName, Pose* p_pPose = NULL);

	void update(float p_dt);

	static ActorManager* Get(void);

	bool VprocessEvent(EventPtr p_event);

private:
	static std::map<ActorType,std::list<ActorPtr> > m_actorMap;
	static std::map<float,std::list<ActorPtr> > m_drawableActorMap;
	static boost::shared_ptr<sf::RenderWindow> m_app;
	static std::list<float> m_levels;
	static unsigned int m_globalId;

	static void addActor(ActorPtr p_actor);
};

