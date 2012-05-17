#include <boost/smart_ptr/shared_ptr.hpp>
#include "AbstractActor.h"
#include "MovableActor.h"
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
	std::map<ActorType,std::list<ActorPtr> > s_actorMap;
	std::map<float,std::list<MovableActorPtr> > s_movableActorMap;

	ActorManager(void);
	ActorManager(boost::shared_ptr<sf::RenderWindow> p_app);
	~ActorManager(void);

	ActorPtr getNewMovableActor(std::string p_actorName);
	void addActor(ActorPtr p_actor);
	void update(float p_dt);

	static ActorManager* Get(void);

private:
	static std::string s_xmlFolder;
	boost::shared_ptr<sf::RenderWindow> m_app;
	std::list<float> m_levels;
	unsigned int m_globalId;

};

