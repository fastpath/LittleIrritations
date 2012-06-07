#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <boost/foreach.hpp>
#include "EnumNames.h"
#include "AbstractActor.h"
#include "DrawableActor.h"
#include "Pose.h"
#include "SceneManager.h"
#include "Player.h"
#include "ActorManager.h"
#include "InputHandler.h"
#include "EventManagerImpl.h"
#include "Settings.h"
#include "Screen.h"

const int FRAMERATE = 60;
const float DT = 1.0/FRAMERATE;
const float EPSILON = 0.01;

EventManagerImpl* m_evtMgr;
boost::shared_ptr<ActorManager> m_actMgr;
Settings* m_settings;
boost::shared_ptr<sf::RenderWindow> Window;
boost::shared_ptr<InputHandler> inputHandler;
boost::shared_ptr<Screen> testChamber;


void initialize(void)
{

	m_settings = new Settings();

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];
		//std::cout << "Mode #" << i << ": "
		//			<< mode.width << "x" << mode.height << " - "
		//			<< mode.bitsPerPixel << " bpp" << std::endl;
	}

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	Window = boost::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(Settings::getUnsignedInt("WIDTH"),Settings::getUnsignedInt("HEIGTH"),desktop.bitsPerPixel),"Little Irritations"/*,sf::Style::Fullscreen*/));
	sf::View view;
	view.reset(sf::FloatRect(0,0,1920,1080));
	//view.rotate(45);
	view.setViewport(sf::FloatRect(0.f, 0.f,1.0f,1.0f));
	Window->setView(view);

	Window->setKeyRepeatEnabled(false);
	sf::ContextSettings cs = Window->getSettings();
	Window->setFramerateLimit(FRAMERATE);

	m_evtMgr = new EventManagerImpl("Super EventManager", true);
	m_actMgr = boost::shared_ptr<ActorManager>(new ActorManager(Window));
	inputHandler = boost::shared_ptr<InputHandler>(new InputHandler(Window));
	

	DrawableActorPtr cody = ActorManager::getNewDrawableActor("cody");

	DrawableActorPtr astroid1 = ActorManager::getNewDrawableActor("astroid1");

	DrawableActorPtr astroid2 = ActorManager::getNewDrawableActor("astroid2");

	DrawableActorPtr astroid3 = ActorManager::getNewDrawableActor("astroid3");

	// Event Testing
	boost::shared_ptr<Player> player(new Player());
	player->setActiveActor(cody);

	boost::shared_ptr<SceneManager> sceneManager(new SceneManager());
	sceneManager->setPlayer(player);
	
	m_evtMgr->VAddEventListener(sceneManager, 5, KEY_PRESSED,MOUSE_MOVED,KEY_RELEASED, MOUSE_DOWN, MOUSE_UP);
	m_evtMgr->VAddEventListener(m_actMgr, 1, CREATE_ACTOR);

	testChamber = boost::shared_ptr<Screen>(new Screen());
	testChamber->initializeFromXML("Levels.xml");

	m_evtMgr->VAddEventListener(testChamber, 1, NEW_ACTOR);
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

		IBaseEventManager::Get()->VProcessEvents(5);
		Window->clear(sf::Color(0,255,255));
		while ( frameTime > 0.0 - EPSILON)
         {
			const float deltaTime = std::min( frameTime, DT );
			ActorManager::Get()->update(deltaTime);

			for (int i=0; i<testChamber->getPathPolygonCount(); ++i)
			{
				testChamber->getPathPolygon(i)->draw(Window);
			}

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