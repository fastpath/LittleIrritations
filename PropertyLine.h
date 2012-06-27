#pragma once
#include "IPropertyActor.h"
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>
#include <cmath>
#include "PropertyPoint.h"

class PropertyLine;
typedef boost::shared_ptr<PropertyLine> PropertyLinePtr;

class PropertyLine : public IPropertyActor
{
public:
	PropertyLine(boost::shared_ptr<sf::Vector3f> p_pStartPoint, boost::shared_ptr<sf::Vector3f> p_pEndPoint);
	PropertyLine(PropertyPointPtr p_pStartPoint, PropertyPointPtr p_pEndPoint);
	~PropertyLine(void);

	PropertyPointPtr getStartPoint(void);
	PropertyPointPtr getEndPoint(void);
	PropertyPointPtr getPathVector(void);

	float distanceToPoint(PropertyPointPtr p_pPoint);
	PropertyPointPtr intersectsWith(PropertyLinePtr p_pOtherLine);

private:
	PropertyPointPtr m_pStartPoint;
	PropertyPointPtr m_pEndPoint;
	PropertyPointPtr m_pathVector;

};

