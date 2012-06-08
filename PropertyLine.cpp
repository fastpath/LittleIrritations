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

boost::shared_ptr<sf::Vector3f> PropertyLine::getPathVector(void)
{
	return boost::shared_ptr<sf::Vector3f>(new sf::Vector3f( (*m_pEndPoint) - (*m_pStartPoint) ) );
}

bool PropertyLine::hasProperty(PropertyType p_type)
{
	bool success = false;
	auto itProp = m_properties.find(p_type);
	if ( itProp != m_properties.end())
	{
		success = true;
		return success;
	}

	return success;
}