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
	case KEY_PRESSED:
		std::cout << "Event beim Player angekommen!" << std::endl;
		break;
	default:
		std::cout << "Default!" << std::endl;
		break;
	}

	return false;
}
