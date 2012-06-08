#pragma once
#include "MovableActor.h"
#include <SFML/Graphics.hpp>
#include "Pose.h"
#include <iostream>
#include <boost/weak_ptr.hpp>

class DrawableActor;
typedef boost::shared_ptr<DrawableActor> DrawableActorStrongPtr;
typedef boost::weak_ptr<DrawableActor> DrawableActorWeakPtr;

class DrawableActor : public MovableActor, public sf::Sprite
{
public:
	DrawableActor(void);
	DrawableActor(int p_id);

	virtual void VsetPosition(float p_x, float p_y, float p_z);
	virtual void VsetPosition(float p_x, float p_y);
	virtual void Vupdate(float p_deltaMs);

	~DrawableActor(void);
};

