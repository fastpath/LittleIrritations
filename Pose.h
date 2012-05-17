#pragma once
#include <SFML/System.hpp>
#include <iostream>

class Pose
{
public:
	Pose(void);
	Pose(float p_x, float p_y, float p_z, float p_rot);
	Pose(float p_x, float p_y, float p_rot);
	Pose(float p_x, float p_y);
	~Pose(void);

	sf::Vector3f getVector3f();
	sf::Vector2f getVector2f();
	float getX(void);
	float getY(void);
	float getZ(void);
	float getRotation();

	void setPosition(float p_x, float p_y, float p_z);
	void setRotation(float p_rot);

	friend std::ostream& operator<<(std::ostream& p_os, Pose& p_val) {
		p_os << "(" << p_val.getVector3f().x  << ", " << p_val.getVector3f().y << "," << p_val.getVector3f().z << ") rot: " << p_val.getRotation();
		return p_os;
	}

private:
	sf::Vector3f m_vector;
	float m_rotation;

};

