#include "Pose.h"


Pose::Pose(void)
{
	m_vector = sf::Vector3f(0.0,0.0,1.0);
	m_rotation = 0.0;
}

Pose::Pose(float p_x, float p_y, float rot){
	m_vector = sf::Vector3f(p_x,p_y,0.0);
	m_rotation = rot;
};

Pose::Pose(float p_x, float p_y){
	m_vector = sf::Vector3f(p_x,p_y,0.0);
	m_rotation = 0.0;
};

Pose::Pose(float p_x, float p_y, float p_z, float p_rot){
	m_vector = sf::Vector3f(p_x,p_y,p_z);
	m_rotation = p_rot;
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

float Pose::getX(void) {
	return m_vector.x;
}

float Pose::getY(void) {
	return m_vector.y;
}

float Pose::getZ(void) {
	return m_vector.z;
}

void Pose::setPosition(float p_x, float p_y, float p_z) {
	m_vector.x = p_x; m_vector.y = p_y; m_vector.z = p_z;
}

void Pose::setRotation(float p_rot) {
	m_rotation = p_rot;
}



Pose::~Pose(void)
{
}
