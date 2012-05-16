#pragma once
#include "AbstractActor.h"
#include "IEventListener.h"
#include "Property.h"
#include <SFML/Window/Keyboard.hpp>
#include "Pose.h"


class Player : public IEventListener
{
public:
	Player(void);
	~Player(void);

	bool VprocessEvent(EventPtr p_event);

	void setActiveActor(ActorPtr p_actor);

private:
	ActorPtr m_activeActor;
};

