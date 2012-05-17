#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <boost/foreach.hpp>
#include "EnumNames.h"
#include "TextureLoader.h"
#include "AbstractActor.h"
#include "MovableActor.h"
#include "Pose.h"
#include "Player.h"
#include "ActorManager.h"
#include "InputHandler.h"
#include "EventManagerImpl.h"

const int FRAMERATE = 60;
const float DT = 1.0/FRAMERATE;
const float EPSILON = 0.01;

EventManagerImpl* m_evtMgr;
ActorManager* m_actMgr;
boost::shared_ptr<sf::RenderWindow> Window;
boost::shared_ptr<InputHandler> inputHandler;


void initialize(void)
{
	Window = boost::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800,600,32),"Little Irritations"));
	Window->setKeyRepeatEnabled(false);
	sf::ContextSettings cs = Window->getSettings();
	Window->setFramerateLimit(FRAMERATE);

	m_evtMgr = new EventManagerImpl("Super EventManager", true);
	m_actMgr = new ActorManager(Window);
	std::cout << "Creating InputHandler" << std::endl;
	inputHandler = boost::shared_ptr<InputHandler>(new InputHandler(Window));

	boost::shared_ptr<AbstractActor> cody(new MovableActor(0));
	boost::shared_ptr<MovableActor> moveCody = boost::shared_dynamic_cast<MovableActor>(cody);
	moveCody->setTexture(*TextureLoader::getTexture("cody2_500x1000"));
	moveCody->setPosition(300.0,300.0);
	moveCody->setScale(0.2,0.2);
	ActorManager::Get()->addActor(cody);

	std::cout << moveCody->getTextureRect().height << std::endl;
	std::cout << moveCody->getGlobalBounds().height << std::endl;

	boost::shared_ptr<AbstractActor> astroid1(new MovableActor(1));
	boost::shared_ptr<MovableActor> moveAstr1 = boost::shared_dynamic_cast<MovableActor>(astroid1);
	moveAstr1->setTexture(*TextureLoader::getTexture("astroid1_600x500"));
	moveAstr1->setPosition(500.0,500.0);
	moveAstr1->setOrigin(300.0,250.0);
	moveAstr1->setScale(0.3,0.3);
	moveAstr1->accelerate(Pose(0.0,0.0,30));
	ActorManager::Get()->addActor(astroid1);

	boost::shared_ptr<AbstractActor> astroid2(new MovableActor(2));
	boost::shared_ptr<MovableActor> moveAstr2 = boost::shared_dynamic_cast<MovableActor>(astroid2);
	moveAstr2->setTexture(*TextureLoader::getTexture("astroid2_600x500"));
	moveAstr2->setPosition(300.0,400.0);
	moveAstr2->setOrigin(300.0,250.0);
	moveAstr2->setScale(0.4,0.4);
	moveAstr2->accelerate(Pose(0.0,0.0,50));
	ActorManager::Get()->addActor(astroid2);

	boost::shared_ptr<AbstractActor> astroid3(new MovableActor(3));
	boost::shared_ptr<MovableActor> moveAstr3 = boost::shared_dynamic_cast<MovableActor>(astroid3);
	moveAstr3->setTexture(*TextureLoader::getTexture("astroid3_550x700"));
	moveAstr3->setPosition(200.0,300.0);
	moveAstr3->setOrigin(225.0,350.0);
	moveAstr3->setScale(0.5,0.5);
	moveAstr3->accelerate(Pose(0.0,0.0,30));
	ActorManager::Get()->addActor(astroid3);

	// Event Testing
	boost::shared_ptr<Player> player(new Player());
	m_evtMgr->VAddEventListener(player, 5, KEY_PRESSED,KEY_RELEASED,MOUSE_MOVED,MOUSE_UP,MOUSE_DOWN);
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