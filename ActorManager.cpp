#include "ActorManager.h"

std::string ActorManager::s_xmlFolder = "../CrackTheSky/data/xml/";
static ActorManager* g_ActorManager = NULL;

ActorManager::ActorManager(boost::shared_ptr<sf::RenderWindow> p_app) {
	if (g_ActorManager)
	{
		delete g_ActorManager;
	}
	g_ActorManager = this;

	m_app = p_app;
}

ActorManager::~ActorManager(void) {
	delete g_ActorManager;
}

ActorManager* ActorManager::Get() {
	return g_ActorManager;
}

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
	switch (p_actor->getType()) {
		case MOVABLE_ACTOR: {
			MovableActorPtr tempPtr = boost::shared_static_cast<MovableActor>(p_actor);
			s_movableActorMap[tempPtr->getZ()].push_back(tempPtr);
			m_levels.push_back(tempPtr->getZ());
		}break;
		default:
			break;
	}
	s_actorMap[p_actor->getType()].push_back(p_actor);
}

void ActorManager::update(float p_dt)
{
	for (auto movableActor = s_actorMap[MOVABLE_ACTOR].begin(); movableActor != s_actorMap[MOVABLE_ACTOR].end(); ++movableActor)
	{
		boost::shared_ptr<MovableActor> movie = boost::shared_dynamic_cast<MovableActor>(*movableActor);
		movie->update(p_dt);
	}

	m_levels.unique();
	m_levels.sort();

	for (auto level = m_levels.begin(); level != m_levels.end(); ++level)
	{
		float tmp = *level;
		std::list<MovableActorPtr> movies = s_movableActorMap[tmp];
		for (auto movActor = movies.begin(); movActor != movies.end(); ++movActor)
		{
			MovableActorPtr tempPtr = *movActor;
			m_app->draw(*tempPtr);
			//std::cout << "draaaw   id#" << tempPtr->getId() << "  " << tempPtr->getPosition().x << "," << tempPtr->getPosition().y << std::endl;
		}
		
	}
}
