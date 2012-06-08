#pragma once
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

	void setActiveActor(DrawableActorWeakPtr p_actor);
	void moveCurrentActorOffsetBased(int xOffset, int yOffset);
	void moveCurrentActorAbsolute(int newX, int newY);
	void accelerateActorToNewPosition(Pose newPose);

private:
	DrawableActorWeakPtr m_activeActor;
};

