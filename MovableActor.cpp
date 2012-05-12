#include "MovableActor.h"


MovableActor::MovableActor(void) : AbstractActor(-1, MOVABLE_ACTOR)
{
	
}

MovableActor::MovableActor(int id) : AbstractActor(id,MOVABLE_ACTOR) {

}

void MovableActor::update(float dt) {
	sf::Vector2f offset = m_acceleration.getVector2f()*dt;
	float rotateOffset = m_acceleration.getRotation()*dt;
	this->move(offset);
	this->rotate(rotateOffset);
	//std::cout << "acc  (" << offset.x << "," << offset.y << ")" << std::endl;
}

void MovableActor::accelerate(Pose& pose) {
	m_acceleration = pose;
}

Pose& MovableActor::getAcceleration() {
	return m_acceleration;
}

MovableActor::~MovableActor(void)
{
}
