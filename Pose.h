#pragma once
#include <SFML/System.hpp>
#include <iostream>

class Pose
{
public:
	Pose(void);
	Pose(float x, float y, float z, float rot);
	Pose(float x, float y, float rot);
	Pose(float x, float y);
	~Pose(void);

	sf::Vector3f getVector3f();
	sf::Vector2f getVector2f();

	float getRotation();

	friend std::ostream& operator<<(std::ostream& os, Pose& val) {
		os << "(" << val.getVector3f().x  << ", " << val.getVector3f().y << "," << val.getVector3f().z << ")";
		return os;
	}

private:
	sf::Vector3f m_vector;
	float m_rotation;

};

