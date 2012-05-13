#include "Player.h"


Player::Player(void)
{
	std::cout << "Player created" << std::endl;
}


Player::~Player(void)
{
}

void Player::setActiveActor(ActorPtr p_actor)
{
	m_activeActor = p_actor;
}

bool Player::VprocessEvent(EventPtr p_event)
{
	switch (p_event->GetEventType())
	{
	case KEY_PRESSED: {
		std::cout << "Key Pressed Event beim Player angekommen!" << std::endl;
		PropertyPtr key = p_event->GetProperty(KEY);
		boost::shared_ptr<TProperty<sf::Keyboard::Key>> tmp = boost::shared_static_cast<TProperty<sf::Keyboard::Key>>(key);
		sf::Keyboard::Key pressedKey = tmp->GetValue();
		switch (pressedKey) {
			case sf::Keyboard::Up: {
				std::cout << "Oben gedrueckt" << std::endl;
				break;
			}
			case sf::Keyboard::Down: {
				std::cout << "Unten gedrueckt" << std::endl;
				break;
			}
			case sf::Keyboard::Right: {
				std::cout << "Rechts gedrueckt" << std::endl;
				break;
			}
			case sf::Keyboard::Left: {
				std::cout << "Links gedrueckt" << std::endl;
				break;
			}
			default:
				std::cout << "Irgendeine Taste wurde gedrueckt" << std::endl;
		}
		break;
	}
	default:
		std::cout << "Default! Player.cpp" << std::endl;
		break;
	}

	return false;
}
