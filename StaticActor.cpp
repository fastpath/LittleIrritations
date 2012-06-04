#include "StaticActor.h"


StaticActor::StaticActor(void) : AbstractActor(-1, STATIC_ACTOR)
{
	this->sf::Sprite::setPosition(0.0,0.0);
}

StaticActor::StaticActor(int p_id) : AbstractActor(p_id, STATIC_ACTOR)
{
	this->sf::Sprite::setPosition(0.0,0.0);
}

void StaticActor::setPosition(float p_x, float p_y, float p_z)
{
	this->sf::Sprite::setPosition(p_x,p_y);
	m_position.setPosition(p_x,p_y,p_z);
}

void StaticActor::setPosition(float p_x, float p_y)
{
	this->sf::Sprite::setPosition(p_x,p_y);
	m_position.setPosition(p_x,p_y,0.0);
}

void StaticActor::update(float p_dt)
{

}


StaticActor::~StaticActor(void)
{
}
