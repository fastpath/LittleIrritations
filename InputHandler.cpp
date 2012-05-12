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
			EventPtr keyPressedEvent(new Event(KEY_PRESSED,0.0f));
			EventPtr keyRepeatEvent(new Event(KEY_REPEAT,0.0f));
			PropertyPtr key;
			switch (sfmlEvent.type)
			{
			case sf::Event::Closed:
				m_app->close();
				break;
			case sf::Event::KeyPressed:
				key = PropertyPtr(new TProperty<sf::Keyboard::Key>(KEY,sfmlEvent.key.code));
				keyPressedEvent->addProperty(key);

				std::cout << "Taste gedrueckt" << std::endl;
				break;
			case sf::Event::KeyReleased:
				

			default:
				break;
			}

			IBaseEventManager::Get()->VQueueEvent(keyPressedEvent);
		}

		
}
