#pragma once
#include "AbstractActor.h"
#include "Pose.h"
#include <iostream>

class MovableActor;
typedef boost::shared_ptr<MovableActor> MovableActorStrongPtr;
typedef boost::weak_ptr<MovableActor> MovableActorWeakPtr;

class MovableActor : public AbstractActor
{
public:
	MovableActor(int p_id, ActorType p_type);
	~MovableActor(void);

	void accelerate(Pose& p_pose);
	Pose& getAcceleration(void);
	float getZ(void);
	virtual void VsetPosition(float p_x, float p_y, float p_z) = 0;
	virtual void VsetPosition(float p_x, float p_y) = 0;

protected:
	Pose m_acceleration;
	Pose m_position;
};

