#include "PropertyLine.h"


PropertyLine::PropertyLine(PropertyPointPtr p_pStartPoint, PropertyPointPtr p_pEndPoint)
{
	m_pStartPoint = p_pStartPoint;
	m_pEndPoint = p_pEndPoint;
	m_pathVector = PropertyPointPtr(new PropertyPoint( (*m_pEndPoint).x - (*m_pStartPoint).x,(*m_pEndPoint).y - (*m_pStartPoint).y,(*m_pEndPoint).z - (*m_pStartPoint).z));
}

PropertyLine::~PropertyLine(void)
{
}

PropertyPointPtr PropertyLine::getStartPoint(void)
{
	return m_pStartPoint;
}

PropertyPointPtr PropertyLine::getEndPoint(void)
{
	return m_pEndPoint;
}

PropertyPointPtr PropertyLine::getPathVector(void)
{
	return m_pathVector;
}

float PropertyLine::length(void)
{
	return m_pathVector->length();
}

float PropertyLine::distanceToPoint(PropertyPointPtr p_pPoint)
{
	float d = ((m_pStartPoint->y - m_pEndPoint->y) * p_pPoint->x + m_pathVector->x * p_pPoint->y + (m_pStartPoint->x*m_pEndPoint->y - m_pEndPoint->x*m_pStartPoint->y) ) / (std::sqrt((m_pEndPoint->x-m_pStartPoint->x)*(m_pEndPoint->x-m_pStartPoint->x)+(m_pStartPoint->y-m_pEndPoint->y)*(m_pStartPoint->y-m_pEndPoint->y)));
	return d;
}

PropertyPointPtr PropertyLine::intersectsWith(PropertyLinePtr p_pOtherLine)
{
	if (p_pOtherLine->getStartPoint().get() == m_pStartPoint.get() || p_pOtherLine->getEndPoint().get() == m_pEndPoint.get() || p_pOtherLine->getStartPoint().get() == m_pEndPoint.get() || p_pOtherLine->getEndPoint().get() == m_pStartPoint.get())
	{
		return PropertyPointPtr();
	}


	float x1 = m_pStartPoint->x, x2 = m_pEndPoint->x, x3 = p_pOtherLine->getStartPoint()->x, x4 = p_pOtherLine->getEndPoint()->x;
	float y1 = m_pStartPoint->y, y2 = m_pEndPoint->y, y3 = p_pOtherLine->getStartPoint()->y, y4 = p_pOtherLine->getEndPoint()->y;
 
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return PropertyPointPtr();
 
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
	// Check if the x and y coordinates are within both lines
	if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
	x < std::min(x3, x4) || x > std::max(x3, x4) ) return PropertyPointPtr();
	if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
	y < std::min(y3, y4) || y > std::max(y3, y4) ) return PropertyPointPtr();
 
	// Return the point of intersection
	PropertyPointPtr ret = PropertyPointPtr(new PropertyPoint());
	ret->x = x;
	ret->y = y;
	return ret;
}
