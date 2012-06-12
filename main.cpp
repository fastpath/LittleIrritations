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
#include "MyProcessManager.h"
#include "PathAnimator.h"

const int FRAMERATE = 60;
const float DT = 1.0/FRAMERATE;
const float EPSILON = 0.00;

EventManagerImpl* m_evtMgr;
boost::shared_ptr<ActorManager> m_actMgr;
Settings* m_settings;
boost::shared_ptr<sf::RenderWindow> Window;
boost::shared_ptr<InputHandler> inputHandler;
boost::shared_ptr<Screen> testChamber;
boost::shared_ptr<MyProcessManager> procMngr;


void initialize(void)
{
	//detect an instance of the game
	//Calculates secondary storage space and memory
	//cpu speed
	//loads resourche cache
		//read from a zip file
	//loads strings
	//script manager
	//event manager
	//game logic and views
	//preloads savegames and resources

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

	DrawableActorWeakPtr cody = ActorManager::getNewDrawableActor("cody");

	DrawableActorWeakPtr astroid1 = ActorManager::getNewDrawableActor("astroid1");

	DrawableActorWeakPtr astroid2 = ActorManager::getNewDrawableActor("astroid2");

	DrawableActorWeakPtr astroid3 = ActorManager::getNewDrawableActor("astroid3");

	// Event Testing
	boost::shared_ptr<Player> player(new Player());
	player->setActiveActor(cody);

	boost::shared_ptr<SceneManager> sceneManager(new SceneManager());
	sceneManager->setPlayer(player);
	
	m_evtMgr->VAddEventListener(sceneManager, 5, KEY_PRESSED,MOUSE_MOVED,KEY_RELEASED, MOUSE_DOWN, MOUSE_UP);
	m_evtMgr->VAddEventListener(boost::shared_dynamic_cast<IEventListener>(m_actMgr), 2, CREATE_ACTOR, MOVE_ACTOR);

	testChamber = boost::shared_ptr<Screen>(new Screen());
	testChamber->initializeFromXML("Levels.xml");

	procMngr = boost::shared_ptr<MyProcessManager>(new MyProcessManager());
	procMngr->attachProcess(boost::shared_dynamic_cast<MyProcess>(m_actMgr));

	m_evtMgr->VAddEventListener(testChamber, 1, NEW_ACTOR);

	boost::shared_ptr<sf::Vector3f> point1 = boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(0,0,0));
	boost::shared_ptr<sf::Vector3f> point2 = boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(100,100,100));
	boost::shared_ptr<sf::Vector3f> point3 = boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(300,300,300));
	boost::shared_ptr<sf::Vector3f> point4 = boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(800,300,300));

	PropertyLinePtr line1 = PropertyLinePtr(new PropertyLine(point1,point2));
	PropertyLinePtr line2 = PropertyLinePtr(new PropertyLine(point2,point3));
	PropertyLinePtr line3 = PropertyLinePtr(new PropertyLine(point3,point4));

	boost::shared_ptr<PathAnimator> pathAnim = boost::shared_ptr<PathAnimator>(new PathAnimator(MovableActorWeakPtr(boost::shared_dynamic_cast<MovableActor>(cody.lock()))));
	pathAnim->addLine(line1);
	pathAnim->addLine(line2);
	pathAnim->addLine(line3);

	procMngr->attachProcess(boost::shared_dynamic_cast<MyProcess>(pathAnim));
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
			float deltaTime = std::min( frameTime, DT );
			procMngr->updateProcesses(deltaTime);
			//ActorManager::Get()->VonUpdate(deltaTime);

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