#include <boost/smart_ptr/shared_ptr.hpp>
#include "AbstractActor.h"
#include "MovableActor.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include "libs\pugixml\pugixml.hpp"

class ActorManager
{
public:
	static std::map<ActorType,std::list<ActorPtr> > s_actorMap;
	static std::map<float,std::list<MovableActorPtr> > s_movableActorMap;

	ActorManager(void);
	ActorManager(boost::shared_ptr<sf::RenderWindow> p_app);
	~ActorManager(void);

	static ActorPtr getNewMovableActor(std::string p_fileName);
	static void addActor(ActorPtr p_actor);
	static void update(float p_dt);

	ActorManager* Get(void);

private:
	static std::string s_xmlFolder;
	boost::shared_ptr<sf::RenderWindow> m_app;
	std::list<float> m_levels;


};

