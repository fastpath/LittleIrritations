#pragma once
#include "IPropertyActor.h"
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>

class PropertyLine;
typedef boost::shared_ptr<PropertyLine> PropertyLinePtr;

class PropertyLine : public IPropertyActor
{
public:
	PropertyLine(boost::shared_ptr<sf::Vector3f> p_pStartPoint, boost::shared_ptr<sf::Vector3f> p_pEndPoint);
	~PropertyLine(void);

	boost::shared_ptr<sf::Vector3f> getStartPoint(void);
	boost::shared_ptr<sf::Vector3f> getEndPoint(void);
	boost::shared_ptr<sf::Vector3f> getPathVector(void);

private:
	boost::shared_ptr<sf::Vector3f> m_pStartPoint;
	boost::shared_ptr<sf::Vector3f> m_pEndPoint;

};

