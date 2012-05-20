#include "SceneManager.h"


SceneManager::SceneManager(void)
{

}


SceneManager::~SceneManager(void)
{

}


bool SceneManager::VprocessEvent(EventPtr p_event)
{
	switch (p_event->GetEventType())
	{
		case KEY_PRESSED: {
			//std::cout << "Key Pressed Event beim SceneManager angekommen!   ";
			sf::Keyboard::Key pressedKey;
			p_event->GetProperty(pressedKey,KEY);

			switch (pressedKey) {
				case sf::Keyboard::Up: {
					//std::cout << "Oben gedrueckt" << std::endl;
				}break;

				case sf::Keyboard::Down: {
					//std::cout << "Unten gedrueckt" << std::endl;
				}break;

				case sf::Keyboard::Right: {
					//std::cout << "Rechts gedrueckt" << std::endl;
				}break;

				case sf::Keyboard::Left: {
					//std::cout << "Links gedrueckt" << std::endl;
				}break;

				default:
					std::cout << "Irgendeine Taste wurde gedrueckt" << std::endl;
			}
		}break;

		case KEY_RELEASED: {
			//std::cout << "Key Released Event beim SceneManager angekommen!" << std::endl;
		}break;
	
		case MOUSE_MOVED: {
			//std::cout << "Mouse Moved Event beim SceneManager angekommen!   ";
			Pose tmpPos;
			p_event->GetProperty(tmpPos,POSE);
			//std::cout << "Position " << tmpPos << std::endl;
			break;
		}
		case MOUSE_DOWN: {
			std::cout << "Mouse Down Event beim SceneManager angekommen!   ";
			Pose tmpPos;
			p_event->GetProperty(tmpPos,POSE);
			int buttonID;
			p_event->GetProperty(buttonID, MOUSEBUTTON);
			std::cout << "Position " << tmpPos << " and ButtonID:" << buttonID << std::endl;
			
			break;
		}
		case MOUSE_UP: {
			std::cout << "Mouse Up Event beim SceneManager angekommen!   ";
			Pose tmpPos;
			p_event->GetProperty(tmpPos,POSE);
			int buttonID;
			p_event->GetProperty(buttonID, MOUSEBUTTON);
			std::cout << "Position " << tmpPos << " and ButtonID:" << buttonID << std::endl;
			if(buttonID == sf::Mouse::Button::Left)
				player->moveCurrentActorAbsolute(tmpPos.getX(), tmpPos.getY());
			else if(buttonID == sf::Mouse::Button::Right)
				player->accelerateActorToNewPosition(tmpPos);
			break;
		}
		default:{
			std::cout << "Default! SceneManager.cpp" << std::endl;
			break;
				std::cout << std::endl;
		}break;
	}
	return false;
}