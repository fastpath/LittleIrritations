#include "PropertyPoint.h"


PropertyPoint::PropertyPoint(float p_x, float p_y, float p_z) : sf::Vector3f(p_x,p_y,p_z)
{
}

PropertyPoint::PropertyPoint(void) : sf::Vector3f(0.0,0.0,0.0)
{
}

PropertyPoint::~PropertyPoint(void)
{
}
