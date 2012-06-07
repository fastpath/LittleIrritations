#include "MovableActor.h"


MovableActor::MovableActor(int p_id, ActorType p_type)  : AbstractActor(p_id, p_type)
{
}


MovableActor::~MovableActor(void)
{
}

Pose& MovableActor::getAcceleration(void)
{
	return m_acceleration;
}

float MovableActor::getZ(void)
{
	return m_position.getZ();
}

void MovableActor::accelerate(Pose& p_pose)
{
	m_acceleration = p_pose;
}
