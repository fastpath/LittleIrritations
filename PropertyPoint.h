#pragma once
#include <SFML/System.hpp>
#include "IPropertyActor.h"
#include <boost\shared_ptr.hpp>

class PropertyPoint;
typedef boost::shared_ptr<PropertyPoint> PropertyPointPtr;

class PropertyPoint : public sf::Vector3f, public IPropertyActor
{
public:
	PropertyPoint(float p_x, float p_y, float p_z);
	~PropertyPoint(void);
};

