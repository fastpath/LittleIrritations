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

DrawableActorWeakPtr ActorManager::getNewDrawableActor(const std::string& p_actorName, Pose* p_pPose) {

	

	pugi::xml_document doc;
	std::string fileName = Settings::getString("XML_PATH")+"DrawableActors.xml";
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	pugi::xml_node root = doc.child("root");
	for (pugi::xml_node actor = root.child("actor"); actor; actor = actor.next_sibling("actor"))
	{
		if ( p_actorName.compare(actor.attribute("name").value()) == 0)
		{
			DrawableActorStrongPtr movie = DrawableActorStrongPtr(new DrawableActor(m_globalId++));
			PropertyPtr nameProp = PropertyPtr(new TProperty<std::string>(NAME,p_actorName));
			movie->addProperty(nameProp);
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
			if (p_pPose != NULL)
			{
				movie->VsetPosition(p_pPose->getX(),p_pPose->getY(),p_pPose->getZ());
			}
			else
			{
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

					if (actor.child("position").attribute("z").empty() == 0)
					{
						std::stringstream z_sstr;
						float z;
						z_sstr<<actor.child("position").attribute("z").value();
						z_sstr>>z;

						movie->VsetPosition(x,y,z);
					}
					else
					{
						movie->setPosition(x,y);
					}
					//std::cout << "position  " << x << y << std::endl;
				}
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
			ActorManager::addActor(movie);
			return DrawableActorWeakPtr(movie);
		}
	}
	return DrawableActorWeakPtr();
}

void ActorManager::addActor(ActorPtr p_actor)
{
	switch (p_actor->getType()) {
		case DRAWABLE_ACTOR: {
			DrawableActorStrongPtr tempPtr = boost::shared_static_cast<DrawableActor>(p_actor);
			m_drawableActorMap[tempPtr->getZ()].push_back(tempPtr);
			m_levels.push_back(tempPtr->getZ());
		}break;
		default:
			break;
	}
	m_actorMap[p_actor->getType()].push_back(p_actor);
}

void ActorManager::VonUpdate(float p_deltaMs)
{
	//std::cout << "How its going" << std::endl;
	for (auto drawableActor = m_actorMap[DRAWABLE_ACTOR].begin(); drawableActor != m_actorMap[DRAWABLE_ACTOR].end(); ++drawableActor)
	{
		boost::shared_ptr<DrawableActor> movie = boost::shared_dynamic_cast<DrawableActor>(*drawableActor);
		movie->Vupdate(p_deltaMs);
	}

	m_levels.unique();
	m_levels.sort();

	//Iterates through the different Z-levels
	for (auto level = m_levels.begin(); level != m_levels.end(); ++level)
	{
		float tmp = *level;
		std::list<ActorPtr> movies = m_drawableActorMap[tmp];
		for (auto actor = movies.begin(); actor != movies.end(); ++actor)
		{
			switch ( (*actor)->getType() )
			{
			case DRAWABLE_ACTOR:
				{
					DrawableActorStrongPtr tempPtr = boost::shared_dynamic_cast<DrawableActor>(*actor);
					//std::string name;
					//tempPtr->GetProperty(name,NAME);
					//std::cout << "Movie name:: " << name << std::endl;
					m_app->draw(*tempPtr);
				} break;
			default:
				break;
			}
			//std::cout << "draaaw   id#" << tempPtr->getId() << "  " << tempPtr->getPosition().x << "," << tempPtr->getPosition().y << std::endl;
		}
		
	}
}

bool ActorManager::VprocessEvent(EventPtr p_event)
{
	switch (p_event->GetEventType())
	{
		case CREATE_ACTOR:
			{
				std::cout << "HALLOOOOO" << std::endl;
				std::string actorName;
				p_event->GetProperty(actorName,NAME);
				std::cout << "Movie name:: " << actorName << std::endl;

				Pose* actorPose = NULL;

				if (p_event->HasProperty(POSE))
				{
					Pose pose;
					p_event->GetProperty(pose,POSE);
					actorPose = &pose;
					std::cout << "Voll der Poser   " << pose << std::endl;
				}
				if (p_event->HasProperty(ACTORTYPE))
				{
					ActorPtr newActor;

					ActorType actorType;
					p_event->GetProperty(actorType,ACTORTYPE);
					switch (actorType)
					{
						case DRAWABLE_ACTOR:
							{
								newActor = ActorManager::getNewDrawableActor(actorName, actorPose).lock();
							} break;
						default:
							break;
					}

					if (newActor != DrawableActorStrongPtr())
					{
						EventPtr newEvent(new Event(NEW_ACTOR,0.0f));

						PropertyPtr newActorPtr = PropertyPtr(new TProperty<ActorPtr>(ACTORPTR,newActor));
						newEvent->addProperty(newActorPtr);

						PropertyPtr newActorName = PropertyPtr(new TProperty<std::string>(NAME,actorName));
						newEvent->addProperty(newActorName);

						IBaseEventManager::Get()->VQueueEvent(newEvent);
						std::cout << "NEW ACTOR MAAN" << std::endl;
					}
				}
				

			}
		default:
			break;
	}

	return true;
}
