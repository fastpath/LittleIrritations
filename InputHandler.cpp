#include "InputHandler.h"


InputHandler::InputHandler(boost::shared_ptr<sf::RenderWindow> p_app)
{
	m_app = p_app;
}


InputHandler::~InputHandler(void)
{
}

void InputHandler::handleKeys() {
		//TProperty<int>* bla =static_cast<TProperty<int>*>(tmp);

		sf::Event sfmlEvent;
		while (m_app->pollEvent(sfmlEvent))
		{
			switch (sfmlEvent.type)
			{
				// CloseEvent
				case sf::Event::Closed: {
					m_app->close();
					break;
				}
				// KeyPressed
				case sf::Event::KeyPressed: {
					EventPtr newEvent(new Event(KEY_PRESSED,0.0f));
					PropertyPtr key = PropertyPtr(new TProperty<sf::Keyboard::Key>(KEY,sfmlEvent.key.code));
					newEvent->addProperty(key);
					IBaseEventManager::Get()->VQueueEvent(newEvent);
				}break;
				// KeyReleased
				case sf::Event::KeyReleased: {
					EventPtr newEvent(new Event(KEY_RELEASED,0.0f));
					PropertyPtr key = PropertyPtr(new TProperty<sf::Keyboard::Key>(KEY,sfmlEvent.key.code));
					newEvent->addProperty(key);
					IBaseEventManager::Get()->VQueueEvent(newEvent);
				}break;
				// MouseMoved
				case sf::Event::MouseMoved:{
					EventPtr newEvent(new Event(MOUSE_MOVED,0.0f));
					Pose tmpPos(sfmlEvent.mouseMove.x,sfmlEvent.mouseMove.y);
					PropertyPtr key = PropertyPtr(new TProperty<Pose>(POSE,tmpPos));
					newEvent->addProperty(key);
					IBaseEventManager::Get()->VQueueEvent(newEvent);
				} break;
				default:
					//std::cout << "Event Type not found!" << std::endl;
				return;
			}
			
		}

		
}
