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
	PropertyLine(PropertyPointPtr p_pStartPoint, PropertyPointPtr p_pEndPoint);
	~PropertyLine(void);

	PropertyPointPtr getStartPoint(void);
	PropertyPointPtr getEndPoint(void);
	PropertyPointPtr getPathVector(void);

	float distanceToPoint(PropertyPointPtr p_pPoint);
	PropertyPointPtr intersectsWith(PropertyLinePtr p_pOtherLine);

	float length(void);

private:
	PropertyPointPtr m_pStartPoint;
	PropertyPointPtr m_pEndPoint;
	PropertyPointPtr m_pathVector;

};

