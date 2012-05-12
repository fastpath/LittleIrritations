#include "ActorManager.h"

std::map<ActorType,std::list<ActorPtr> > ActorManager::s_actorMap;
std::string ActorManager::s_xmlFolder = "../CrackTheSky/data/xml/";

ActorPtr ActorManager::getNewMovableActor(std::string actorName) {
	pugi::xml_document doc;
	std::string fileName = s_xmlFolder+"MovableActors.xml";

	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("root").child("actor").attribute("name").value() << std::endl;

	boost::shared_ptr<AbstractActor> smartPtr(new MovableActor());

	return smartPtr;
}

void ActorManager::addActor(ActorPtr p_actor)
{
	s_actorMap[p_actor->getType()].push_back(p_actor);
}

void ActorManager::update(float p_dt)
{
	for (auto movableActor = s_actorMap[MOVABLE_ACTOR].begin(); movableActor != s_actorMap[MOVABLE_ACTOR].end(); ++movableActor)
	{
		boost::shared_ptr<MovableActor> movie = boost::shared_dynamic_cast<MovableActor>(*movableActor);
		movie->update(p_dt);
	}
}
