#pragma once
#include "AbstractActor.h"
#include "IEventListener.h"


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

