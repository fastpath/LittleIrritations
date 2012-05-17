#pragma once
#include "AbstractActor.h"
#include <SFML/Graphics.hpp>
#include "Pose.h"
#include <iostream>

class MovableActor;
typedef boost::shared_ptr<MovableActor> MovableActorPtr;

class MovableActor : public AbstractActor, public sf::Sprite
{
public:
	MovableActor(void);
	MovableActor(int p_id);

	void accelerate(Pose& p_pose);
	Pose& getAcceleration(void);
	float getZ(void);
	void setPosition(float p_x, float p_y, float p_z);
	void setPosition(float p_x, float p_y);
	void update(float p_dt);

	~MovableActor(void);

private:
	Pose m_acceleration;
	Pose m_position;
};

