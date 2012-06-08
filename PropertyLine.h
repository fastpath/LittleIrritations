#pragma once
#include "Property.h"
#include <map>
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>

class PropertyLine;
typedef boost::shared_ptr<PropertyLine> PropertyLinePtr;

class PropertyLine
{
public:
	PropertyLine(boost::shared_ptr<sf::Vector3f> p_pStartPoint, boost::shared_ptr<sf::Vector3f> p_pEndPoint);
	~PropertyLine(void);

	bool hasProperty(PropertyType p_type);
	void addProperty(PropertyPtr p_property);

	template <typename T>
	void GetProperty(T& p_value, PropertyType p_type) {
		PropertyPtr prop = m_properties[p_type];
		boost::shared_ptr<TProperty<T>> tmp = boost::shared_static_cast<TProperty<T>>(prop);
		p_value = tmp->GetValue();
	}

	boost::shared_ptr<sf::Vector3f> getStartPoint(void);
	boost::shared_ptr<sf::Vector3f> getPathVector(void);

private:
	std::map<PropertyType,PropertyPtr>  m_properties;

	boost::shared_ptr<sf::Vector3f> m_pStartPoint;
	boost::shared_ptr<sf::Vector3f> m_pEndPoint;

};

