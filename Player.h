#pragma once
#include "AbstractActor.h"
#include "IEventListener.h"
#include "Property.h"
#include <SFML/Window.hpp>
#include "Pose.h"
#include "DrawableActor.h"


class Player : public IEventListener
{
public:
	Player(void);
	~Player(void);

	bool VprocessEvent(EventPtr p_event);

	void setActiveActor(DrawableActorPtr p_actor);
	void moveCurrentActorOffsetBased(int xOffset, int yOffset);
	void moveCurrentActorAbsolute(int newX, int newY);
	void accelerateActorToNewPosition(Pose newPose);

private:
	DrawableActorPtr m_activeActor;
};

