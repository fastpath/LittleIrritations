#include "PropertyLine.h"


PropertyLine::PropertyLine(boost::shared_ptr<sf::Vector3f> p_pStartPoint, boost::shared_ptr<sf::Vector3f> p_pEndPoint)
{
	m_pStartPoint = p_pStartPoint;
	m_pEndPoint = p_pEndPoint;
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
	return boost::shared_ptr<sf::Vector3f>(new sf::Vector3f( (*m_pEndPoint) - (*m_pStartPoint) ) );
}