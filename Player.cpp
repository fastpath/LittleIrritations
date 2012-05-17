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
		std::cout << "Key Pressed Event beim Player angekommen!   ";
		sf::Keyboard::Key pressedKey;
		p_event->GetProperty(pressedKey,KEY);
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
	case MOUSE_MOVED: {
		//std::cout << "Mouse Moved Event beim Player angekommen!   ";
		Pose tmpPos;
		p_event->GetProperty(tmpPos,POSE);
		//std::cout << "Position " << tmpPos << std::endl;
		break;
	}
	case MOUSE_DOWN: {
		std::cout << "Mouse Down Event beim Player angekommen!   ";
		Pose tmpPos;
		p_event->GetProperty(tmpPos,POSE);
		int buttonID;
		p_event->GetProperty(buttonID, MOUSEBUTTON);
		std::cout << "Position " << tmpPos << " and ButtonID:" << buttonID << std::endl;
		break;
	}
	case MOUSE_UP: {
		std::cout << "Mouse Up Event beim Player angekommen!   ";
		Pose tmpPos;
		p_event->GetProperty(tmpPos,POSE);
		int buttonID;
		p_event->GetProperty(buttonID, MOUSEBUTTON);
		std::cout << "Position " << tmpPos << " and ButtonID:" << buttonID << std::endl;
		break;
	}
	case KEY_RELEASED: {
		std::cout << "Key Released Event beim Player angekommen!" << std::endl;
		break;
	}
	default:
		std::cout << "Default! Player.cpp" << std::endl;
		break;
	}

	return false;
}
