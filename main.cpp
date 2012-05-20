#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <boost/foreach.hpp>
#include "EnumNames.h"
#include "AbstractActor.h"
#include "MovableActor.h"
#include "Pose.h"
#include "SceneManager.h"
#include "Player.h"
#include "ActorManager.h"
#include "InputHandler.h"
#include "EventManagerImpl.h"
#include "Settings.h"

const int FRAMERATE = 60;
const float DT = 1.0/FRAMERATE;
const float EPSILON = 0.01;

EventManagerImpl* m_evtMgr;
ActorManager* m_actMgr;
Settings* m_settings;
boost::shared_ptr<sf::RenderWindow> Window;
boost::shared_ptr<InputHandler> inputHandler;


void initialize(void)
{

	m_settings = new Settings();

	Window = boost::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800,600,32),"Little Irritations"));
	Window->setKeyRepeatEnabled(false);
	sf::ContextSettings cs = Window->getSettings();
	Window->setFramerateLimit(FRAMERATE);

	m_evtMgr = new EventManagerImpl("Super EventManager", true);
	m_actMgr = new ActorManager(Window);
	inputHandler = boost::shared_ptr<InputHandler>(new InputHandler(Window));
	

	MovableActorPtr cody = ActorManager::Get()->getNewMovableActor("cody");
	ActorManager::Get()->addActor(cody);

	MovableActorPtr astroid1 = ActorManager::Get()->getNewMovableActor("astroid1");
	ActorManager::Get()->addActor(astroid1);

	MovableActorPtr astroid2 = ActorManager::Get()->getNewMovableActor("astroid2");
	ActorManager::Get()->addActor(astroid2);

	MovableActorPtr astroid3 = ActorManager::Get()->getNewMovableActor("astroid3");
	ActorManager::Get()->addActor(astroid3);

	// Event Testing
	boost::shared_ptr<Player> player(new Player());
	player->setActiveActor(cody);

	boost::shared_ptr<SceneManager> sceneManager(new SceneManager());
	sceneManager->setPlayer(player);
	m_evtMgr->VAddEventListener(sceneManager, 5, KEY_PRESSED,MOUSE_MOVED,KEY_RELEASED, MOUSE_DOWN, MOUSE_UP);
}

int main ()
{

	initialize();

	sf::Clock clock;
	float t = 0.0;
	float speed = 400.0;
	sf::Time currentTime = clock.getElapsedTime();

	while (Window->isOpen())
	{
		sf::Time newTime = clock.getElapsedTime();
		float frameTime = newTime.asSeconds() - currentTime.asSeconds();
		//std::cout << " time  " << frameTime << std::endl;
        currentTime = newTime;

		inputHandler->handleKeys();


		//sf::Vector2f direction = actors[0]->getAcceleration().getVector2f();
		//std::cout << "Acc x " << cody->getAcceleration().getDirection().x << "  y " << cody->getAcceleration().getDirection().y << std::endl;
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			direction.y = -speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			direction.y = speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction.x = speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction.x = -speed;
		}
		actors[0]->accelerate(Pose(direction.x,direction.y,0));
		*/
		IBaseEventManager::Get()->VProcessEvents(5);
		Window->clear(sf::Color(0,255,255));
		while ( frameTime > 0.0 - EPSILON)
         {
			const float deltaTime = std::min( frameTime, DT );

			ActorManager::Get()->update(deltaTime);

            frameTime -= DT;
            t += deltaTime;
         }


		/*
		BOOST_FOREACH (boost::shared_ptr<MovableActor> actor, actors) {
			Window->draw(*actor);
		}
		*/
		Window->display();
	}

	return 0;
}