#include "ActorManager.h"

std::string ActorManager::s_xmlFolder = "data/xml/";
static ActorManager* g_ActorManager = NULL;

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

MovableActorPtr ActorManager::getNewMovableActor(std::string p_actorName) {

	MovableActorPtr movie = MovableActorPtr(new MovableActor(m_globalId++));

	pugi::xml_document doc;
	std::string fileName = Settings::getString("XML_PATH")+"MovableActors.xml";
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	pugi::xml_node root = doc.child("root");
	for (pugi::xml_node actor = root.child("actor"); actor; actor = actor.next_sibling("actor"))
	{
		if ( p_actorName.compare(actor.attribute("name").value()) == 0)
		{
			for (pugi::xml_node attribute = actor.child("attribute"); attribute; attribute = attribute.next_sibling("attribute"))
			{
				if (std::string("texture").compare(attribute.attribute("key").value()) == 0)
				{
					//std::cout << "texture  " << attribute.attribute("value").value() << std::endl;
					movie->setTexture(*TextureLoader::getTexture(attribute.attribute("value").value()));
				} 
				if (std::string("scale").compare(attribute.attribute("key").value()) == 0)
				{
					
					std::stringstream x_sstr;
					float x;
					x_sstr<<attribute.attribute("x").value();
					x_sstr>>x;
					std::stringstream y_sstr;
					float y;
					y_sstr<<attribute.attribute("y").value();
					y_sstr>>y;
					//std::cout << "scale  " << x << "," << y << std::endl;
					movie->setScale(x,y);

				} 
				if (std::string("origin").compare(attribute.attribute("key").value()) == 0)
				{
					//std::cout << "origin  " << std::endl;
					std::stringstream x_sstr;
					float x;
					x_sstr<<attribute.attribute("x").value();
					x_sstr>>x;
					std::stringstream y_sstr;
					float y;
					y_sstr<<attribute.attribute("y").value();
					y_sstr>>y;
					
					movie->setOrigin(x,y);
				} 
				if (std::string("position").compare(attribute.attribute("key").value()) == 0)
				{
					std::stringstream x_sstr;
					float x;
					x_sstr<<attribute.attribute("x").value();
					x_sstr>>x;
					std::stringstream y_sstr;
					float y;
					y_sstr<<attribute.attribute("y").value();
					y_sstr>>y;

					//std::cout << "position  " << x << y << std::endl;

					movie->setPosition(x,y);
				} 
				if (std::string("acceleration").compare(attribute.attribute("key").value()) == 0)
				{
					std::stringstream x_sstr;
					float x;
					x_sstr<<attribute.attribute("x").value();
					x_sstr>>x;
					std::stringstream y_sstr;
					float y;
					y_sstr<<attribute.attribute("y").value();
					y_sstr>>y;
					std::stringstream rot_sstr;
					float rot;
					rot_sstr<<attribute.attribute("rotation").value();
					rot_sstr>>rot;
					//std::cout << "acc  " << x << ", " << y << ", " << rot << std::endl;
					movie->accelerate(Pose(x,y,rot));
				}

			}
		}



	}

	return movie;
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
