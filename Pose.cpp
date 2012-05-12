#include "Pose.h"


Pose::Pose(void)
{
	m_vector = sf::Vector3f(0.0,0.0,1.0);
	m_rotation = 0.0;
}

Pose::Pose(float x, float y, float rot){
	m_vector = sf::Vector3f(x,y,0.0);
	m_rotation = rot;
};

Pose::Pose(float x, float y, float z, float rot){
	m_vector = sf::Vector3f(x,y,z);
	m_rotation = rot;
};

float Pose::getRotation() {
	return m_rotation;
}

sf::Vector3f Pose::getVector3f() {
	return m_vector;
}

sf::Vector2f Pose::getVector2f() {
	return sf::Vector2f(m_vector.x,m_vector.y);
}

Pose::~Pose(void)
{
}
