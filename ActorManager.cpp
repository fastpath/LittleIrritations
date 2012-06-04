#include "ActorManager.h"

static ActorManager* g_ActorManager = NULL;
std::map<ActorType,std::list<ActorPtr> > ActorManager::m_actorMap;
std::map<float,std::list<ActorPtr> > ActorManager::m_drawableActorMap;
boost::shared_ptr<sf::RenderWindow> ActorManager::m_app;
std::list<float> ActorManager::m_levels;
unsigned int ActorManager::m_globalId;

ActorManager::ActorManager(boost::shared_ptr<sf::RenderWindow> p_app) {
	if (g_ActorManager)
	{
		delete g_ActorManager;
	}
	g_ActorManager = this;

	m_app = p_app;
	m_globalId = 0;
}

ActorManager::~ActorManager(void) {
	delete g_ActorManager;
}

ActorManager* ActorManager::Get() {
	return g_ActorManager;
}

MovableActorPtr ActorManager::getNewMovableActor(const std::string& p_actorName) {

	MovableActorPtr movie = MovableActorPtr(new MovableActor(m_globalId++));

	pugi::xml_document doc;
	std::string fileName = Settings::getString("XML_PATH")+"MovableActors.xml";
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	pugi::xml_node root = doc.child("root");
	for (pugi::xml_node actor = root.child("actor"); actor; actor = actor.next_sibling("actor"))
	{
		if ( p_actorName.compare(actor.attribute("name").value()) == 0)
		{

			if (actor.child("texture").empty() == 0)
			{
				//std::cout << "texture  " << attribute.attribute("value").value() << std::endl;
				movie->setTexture(*TextureLoader::getTexture(actor.child("texture").attribute("value").value()));
			} 
			if (actor.child("scale").empty() == 0)
			{
					
				std::stringstream x_sstr;
				float x;
				x_sstr<<actor.child("scale").attribute("x").value();
				x_sstr>>x;
				std::stringstream y_sstr;
				float y;
				y_sstr<<actor.child("scale").attribute("y").value();
				y_sstr>>y;
				//std::cout << "scale  " << x << "," << y << std::endl;
				movie->setScale(x,y);

			} 
			if (actor.child("origin").empty() == 0)
			{
				//std::cout << "origin  " << std::endl;
				std::stringstream x_sstr;
				float x;
				x_sstr<<actor.child("origin").attribute("x").value();
				x_sstr>>x;
				std::stringstream y_sstr;
				float y;
				y_sstr<<actor.child("origin").attribute("y").value();
				y_sstr>>y;
					
				movie->setOrigin(x,y);
			} 
			if (actor.child("position").empty() == 0)
			{
				std::stringstream x_sstr;
				float x;
				x_sstr<<actor.child("position").attribute("x").value();
				x_sstr>>x;
				std::stringstream y_sstr;
				float y;
				y_sstr<<actor.child("position").attribute("y").value();
				y_sstr>>y;

				//std::cout << "position  " << x << y << std::endl;

				movie->setPosition(x,y);
			} 
			if (actor.child("acceleration").empty() == 0)
			{
				std::stringstream x_sstr;
				float x;
				x_sstr<<actor.child("acceleration").attribute("x").value();
				x_sstr>>x;
				std::stringstream y_sstr;
				float y;
				y_sstr<<actor.child("acceleration").attribute("y").value();
				y_sstr>>y;
				std::stringstream rot_sstr;
				float rot;
				rot_sstr<<actor.child("acceleration").attribute("rotation").value();
				rot_sstr>>rot;
				//std::cout << "acc  " << x << ", " << y << ", " << rot << std::endl;
				movie->accelerate(Pose(x,y,rot));
			}
		}
	}

	ActorManager::addActor(movie);

	return movie;
}

StaticActorPtr ActorManager::getNewStaticActor(const std::string& p_actorName)
{
	StaticActorPtr staty = StaticActorPtr(new StaticActor(m_globalId++));

	pugi::xml_document doc;
	std::string fileName = Settings::getString("XML_PATH")+"StaticActors.xml";
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	pugi::xml_node root = doc.child("root");
	for (pugi::xml_node actor = root.child("actor"); actor; actor = actor.next_sibling("actor"))
	{
		if ( p_actorName.compare(actor.attribute("name").value()) == 0)
		{
			if (actor.child("texture").empty() == 0)
			{
				//std::cout << "texture  " << attribute.attribute("value").value() << std::endl;
				staty->setTexture(*TextureLoader::getTexture(actor.child("texture").attribute("value").value()));
			} 
		}
	}

	ActorManager::addActor(staty);

	return staty;
}

void ActorManager::addActor(ActorPtr p_actor)
{
	switch (p_actor->getType()) {
		case MOVABLE_ACTOR: {
			MovableActorPtr tempPtr = boost::shared_static_cast<MovableActor>(p_actor);
			m_drawableActorMap[tempPtr->getZ()].push_back(tempPtr);
			m_levels.push_back(tempPtr->getZ());
		}break;
		default:
			break;
	}
	m_actorMap[p_actor->getType()].push_back(p_actor);
}

void ActorManager::update(float p_dt)
{
	for (auto movableActor = m_actorMap[MOVABLE_ACTOR].begin(); movableActor != m_actorMap[MOVABLE_ACTOR].end(); ++movableActor)
	{
		boost::shared_ptr<MovableActor> movie = boost::shared_dynamic_cast<MovableActor>(*movableActor);
		movie->update(p_dt);
	}

	m_levels.unique();
	m_levels.sort();

	for (auto level = m_levels.begin(); level != m_levels.end(); ++level)
	{
		float tmp = *level;
		std::list<ActorPtr> movies = m_drawableActorMap[tmp];
		for (auto actor = movies.begin(); actor != movies.end(); ++actor)
		{
			switch ( (*actor)->getType() )
			{
			case MOVABLE_ACTOR:
				{
					MovableActorPtr tempPtr = boost::shared_dynamic_cast<MovableActor>(*actor);
					m_app->draw(*tempPtr);
				} break;
			case STATIC_ACTOR:
				{
					StaticActorPtr tempPtr = boost::shared_dynamic_cast<StaticActor>(*actor);
					m_app->draw(*tempPtr);
				} break;
			default:
				break;
			}
			//std::cout << "draaaw   id#" << tempPtr->getId() << "  " << tempPtr->getPosition().x << "," << tempPtr->getPosition().y << std::endl;
		}
		
	}
}
