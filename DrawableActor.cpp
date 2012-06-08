#include "DrawableActor.h"


DrawableActor::DrawableActor(void) : MovableActor(-1,DRAWABLE_ACTOR)
{
	this->sf::Sprite::setPosition(0.0,0.0);	
}

DrawableActor::DrawableActor(int p_id) : MovableActor(p_id,DRAWABLE_ACTOR)
{
	this->sf::Sprite::setPosition(0.0,0.0);
}

void DrawableActor::Vupdate(float p_deltaMs)
{
	sf::Vector2f offset = m_acceleration.getVector2f()*p_deltaMs;
	float rotateOffset = m_acceleration.getRotation()*p_deltaMs;
	this->move(offset);
	this->rotate(rotateOffset);
	MovableActor::m_position.setPosition(this->getPosition().x,this->getPosition().y,this->getZ());
	MovableActor::m_position.setRotation(this->getRotation());
	//std::cout << "acc  (" << offset.x << "," << offset.y << ")" << std::endl;
}


void DrawableActor::VsetPosition(float p_x, float p_y, float p_z)
{
	this->sf::Sprite::setPosition(p_x,p_y);
	MovableActor::m_position.setPosition(p_x,p_y,p_z);
}

void DrawableActor::VsetPosition(float p_x, float p_y)
{
	this->sf::Sprite::setPosition(p_x,p_y);
	MovableActor::m_position.setPosition(p_x,p_y,0.0f);
}


DrawableActor::~DrawableActor(void)
{
}