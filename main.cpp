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
#include "ActorManager.h"
#include "InputHandler.h"
#include "EventManagerImpl.h"

const int FRAMERATE = 60;
const float DT = 1.0/FRAMERATE;
const float EPSILON = 0.01;

EventManagerImpl* m_evtMgr;


void initialize(void)
{
	m_evtMgr = new EventManagerImpl("Super EventManager", true);

	boost::shared_ptr<AbstractActor> cody(new MovableActor());
	boost::shared_ptr<MovableActor> moveCody = boost::shared_dynamic_cast<MovableActor>(cody);
	moveCody->setTexture(*TextureLoader::getTexture("cody2_500x1000"));
	moveCody->setPosition(300.0,300.0);
	moveCody->setScale(0.2,0.2);
	ActorManager::addActor(cody);

	std::cout << moveCody->getTextureRect().height << std::endl;
	std::cout << moveCody->getGlobalBounds().height << std::endl;

	boost::shared_ptr<AbstractActor> astroid1(new MovableActor());
	boost::shared_ptr<MovableActor> moveAstr1 = boost::shared_dynamic_cast<MovableActor>(astroid1);
	moveAstr1->setTexture(*TextureLoader::getTexture("astroid1_600x500"));
	moveAstr1->setPosition(500.0,500.0);
	moveAstr1->setOrigin(300.0,250.0);
	moveAstr1->setScale(0.3,0.3);
	moveAstr1->accelerate(Pose(0.0,0.0,30));
	ActorManager::addActor(astroid1);

	boost::shared_ptr<AbstractActor> astroid2(new MovableActor());
	boost::shared_ptr<MovableActor> moveAstr2 = boost::shared_dynamic_cast<MovableActor>(astroid2);
	moveAstr2->setTexture(*TextureLoader::getTexture("astroid2_600x500"));
	moveAstr2->setPosition(300.0,400.0);
	moveAstr2->setOrigin(300.0,250.0);
	moveAstr2->setScale(0.4,0.4);
	moveAstr2->accelerate(Pose(0.0,0.0,50));
	ActorManager::addActor(astroid2);

	boost::shared_ptr<AbstractActor> astroid3(new MovableActor());
	boost::shared_ptr<MovableActor> moveAstr3 = boost::shared_dynamic_cast<MovableActor>(astroid3);
	moveAstr3->setTexture(*TextureLoader::getTexture("astroid3_550x700"));
	moveAstr3->setPosition(200.0,300.0);
	moveAstr3->setOrigin(225.0,350.0);
	moveAstr3->setScale(0.5,0.5);
	moveAstr3->accelerate(Pose(0.0,0.0,30));
	ActorManager::addActor(astroid3);
}

int main ()
{

	initialize();

	boost::shared_ptr<sf::RenderWindow> Window(new sf::RenderWindow(sf::VideoMode(800,600,32),"Crack the Sky"));
	Window->setKeyRepeatEnabled(false);
	
	sf::ContextSettings cs = Window->getSettings();

	//ActorManager::getNewMovableActor("cody");

	sf::Clock clock;

	float t = 0.0;
	float speed = 400.0;
	sf::Time currentTime = clock.getElapsedTime();

	Window->setFramerateLimit(FRAMERATE);

		
	std::cout << "Creating InputHandler" << std::endl;
	boost::shared_ptr<InputHandler> input(new InputHandler(Window));


	while (Window->isOpen())
	{
		sf::Time newTime = clock.getElapsedTime();
		float frameTime = newTime.asSeconds() - currentTime.asSeconds();
		//std::cout << " time  " << frameTime << std::endl;
        currentTime = newTime;
		
		input->handleKeys();

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

		while ( frameTime > 0.0 - EPSILON)
         {
			const float deltaTime = std::min( frameTime, DT );

			/*BOOST_FOREACH (boost::shared_ptr<MovableActor> actor, actors) {
				actor->update(deltaTime);
			}*/

            frameTime -= DT;
            t += deltaTime;
         }
		Window->clear(sf::Color(0,255,255));
		/*BOOST_FOREACH (boost::shared_ptr<MovableActor> actor, actors) {
			Window->draw(*actor);
		}*/
		Window->display();
	}

	return 0;
}