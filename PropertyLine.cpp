#include "PropertyLine.h"


PropertyLine::PropertyLine(boost::shared_ptr<sf::Vector3f> p_pStartPoint, boost::shared_ptr<sf::Vector3f> p_pEndPoint)
{
	m_pStartPoint = p_pStartPoint;
	m_pEndPoint = p_pEndPoint;
	m_pathVector = boost::shared_ptr<sf::Vector3f>(new sf::Vector3f( (*m_pEndPoint) - (*m_pStartPoint) ) );
}


PropertyLine::~PropertyLine(void)
{
}

boost::shared_ptr<sf::Vector3f> PropertyLine::getStartPoint(void)
{
	return m_pStartPoint;
}

boost::shared_ptr<sf::Vector3f> PropertyLine::getEndPoint(void)
{
	return m_pEndPoint;
}

boost::shared_ptr<sf::Vector3f> PropertyLine::getPathVector(void)
{
	return m_pathVector;
}

float PropertyLine::distanceToPoint(boost::shared_ptr<sf::Vector3f> p_pPoint)
{
	float d = ((m_pStartPoint->y - m_pStartPoint->y) * p_pPoint->x + m_pathVector->x * p_pPoint->y + (m_pStartPoint->x*m_pEndPoint->y - m_pEndPoint->x*m_pStartPoint->y) ) / ()

}
