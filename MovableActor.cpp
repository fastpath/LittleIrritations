#include "MovableActor.h"


MovableActor::MovableActor(void) : AbstractActor(-1, MOVABLE_ACTOR)
{
	this->sf::Sprite::setPosition(0.0,0.0);	
}

MovableActor::MovableActor(int p_id) : AbstractActor(p_id,MOVABLE_ACTOR)
{
	this->sf::Sprite::setPosition(0.0,0.0);
}

void MovableActor::update(float p_dt)
{
	sf::Vector2f offset = m_acceleration.getVector2f()*p_dt;
	float rotateOffset = m_acceleration.getRotation()*p_dt;
	this->move(offset);
	this->rotate(rotateOffset);
	m_position.setPosition(this->getPosition().x,this->getPosition().y,this->getZ());
	m_position.setRotation(this->getRotation());
	//std::cout << "acc  (" << offset.x << "," << offset.y << ")" << std::endl;
}

void MovableActor::accelerate(Pose& p_pose)
{
	m_acceleration = p_pose;
}

void MovableActor::setPosition(float p_x, float p_y, float p_z)
{
	this->sf::Sprite::setPosition(p_x,p_y);
	m_position.setPosition(p_x,p_y,p_z);
}

void MovableActor::setPosition(float p_x, float p_y)
{
	this->sf::Sprite::setPosition(p_x,p_y);
	m_position.setPosition(p_x,p_y,0.0f);
}

Pose& MovableActor::getAcceleration(void)
{
	return m_acceleration;
}

float MovableActor::getZ(void)
{
	return m_position.getZ();
}

MovableActor::~MovableActor(void)
{
}