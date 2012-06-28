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

float PropertyPoint::length(void)
{
	return std::sqrt(x*x + y*y + z*z);
}

//std::ostream& PropertyPoint::operator<<(const PropertyPoint& p_lhs)
//{
//	std::ostream o;
//	o << x << y << z;
//	return o;
//
//}
