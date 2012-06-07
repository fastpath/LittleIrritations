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
					PropertyPtr position = PropertyPtr(new TProperty<Pose>(POSE,tmpPos));
					newEvent->addProperty(position);

					IBaseEventManager::Get()->VQueueEvent(newEvent);
				} break;
				// MouseDown
				case sf::Event::MouseButtonPressed:{
					EventPtr newEvent(new Event(MOUSE_DOWN,0.0f));

					sf::Vector2i mouseCoords(sfmlEvent.mouseButton.x,sfmlEvent.mouseButton.y);
					sf::Vector2f viewCoords = m_app->convertCoords(mouseCoords);

					Pose tmpPos(viewCoords.x,viewCoords.y);
					PropertyPtr position = PropertyPtr(new TProperty<Pose>(POSE,tmpPos));
					newEvent->addProperty(position);

					PropertyPtr button = PropertyPtr(new TProperty<sf::Mouse::Button>(MOUSEBUTTON, sfmlEvent.mouseButton.button));
					newEvent->addProperty(button);

					IBaseEventManager::Get()->VQueueEvent(newEvent);
				} break;
				// MouseUp
				case sf::Event::MouseButtonReleased:{
					EventPtr newEvent(new Event(MOUSE_UP,0.0f));

					sf::Vector2i mouseCoords(sfmlEvent.mouseButton.x,sfmlEvent.mouseButton.y);
					sf::Vector2f viewCoords = m_app->convertCoords(mouseCoords);

					Pose tmpPos(viewCoords.x,viewCoords.y);
					PropertyPtr position = PropertyPtr(new TProperty<Pose>(POSE,tmpPos));
					newEvent->addProperty(position);

					PropertyPtr button = PropertyPtr(new TProperty<sf::Mouse::Button>(MOUSEBUTTON, sfmlEvent.mouseButton.button));
					newEvent->addProperty(button);

					IBaseEventManager::Get()->VQueueEvent(newEvent);
				} break;				
				default:
					//std::cout << "Event Type not found!" << std::endl;
				return;
			}
			
		}

		
}
