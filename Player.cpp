#include "Player.h"


Player::Player(void)
{
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

		break;
	default:
		break;
	}

	return false;
}
