#pragma once
#include "AbstractActor.h"
#include "Pose.h"
#include <SFML/Graphics.hpp>

class StaticActor;
typedef boost::shared_ptr<StaticActor> StaticActorPtr;

class StaticActor : public AbstractActor, public sf::Sprite
{
public:
	StaticActor(void);
	StaticActor(int p_id);

	void setPosition(float p_x, float p_y, float p_z);
	void setPosition(float p_x, float p_y);

	void update(float p_dt);

	~StaticActor(void);

private:
	Pose m_position;
};

