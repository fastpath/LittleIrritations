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

	ActorManager(void);
	~ActorManager(void);

	static ActorPtr getNewMovableActor(std::string p_fileName);
	static void addActor(ActorPtr p_actor);
	static void update(float p_dt);


private:
	static std::string s_xmlFolder;


};

