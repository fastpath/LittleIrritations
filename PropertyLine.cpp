#include "PropertyLine.h"


PropertyLine::PropertyLine(boost::shared_ptr<sf::Vector3f> p_pStartPoint, boost::shared_ptr<sf::Vector3f> p_pEndPoint)
{
	m_pStartPoint = p_pStartPoint;
	m_pEndPoint = p_pEndPoint;
	m_pathVector = boost::shared_ptr<sf::Vector3f>(new sf::Vector3f( (*m_pEndPoint) - (*m_pStartPoint) ) );
}

PropertyLine::PropertyLine(PropertyPointPtr p_pStartPoint, PropertyPointPtr p_pEndPoint)
{
	m_pStartPoint = p_pStartPoint;
	m_pEndPoint = p_pEndPoint;
	m_pathVector = PropertyPointPtr(new sf::Vector3f( (*m_pEndPoint) - (*m_pStartPoint) ) );
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

float PropertyLine::distanceToPoint(PropertyPointPtr p_pPoint)
{
	float d = ((m_pStartPoint->y - m_pStartPoint->y) * p_pPoint->x + m_pathVector->x * p_pPoint->y + (m_pStartPoint->x*m_pEndPoint->y - m_pEndPoint->x*m_pStartPoint->y) ) / (std::sqrt((m_pEndPoint->x-m_pStartPoint->x)*(m_pEndPoint->x-m_pStartPoint->x)+(m_pStartPoint->y-m_pEndPoint->y));
	return d;
}
