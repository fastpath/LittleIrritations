#pragma once
#include <SFML/System.hpp>

class Pose
{
public:
	Pose(void);
	Pose(float x, float y, float z, float rot);
	Pose(float x, float y, float rot);
	~Pose(void);

	sf::Vector3f getVector3f();
	sf::Vector2f getVector2f();

	float getRotation();
private:
	sf::Vector3f m_vector;
	float m_rotation;

};

