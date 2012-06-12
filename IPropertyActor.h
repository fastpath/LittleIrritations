#pragma once
#include "Property.h"
#include <boost/shared_ptr.hpp>
#include <map>

class IPropertyActor
{
public:
	IPropertyActor(void);
	~IPropertyActor(void);

	bool hasProperty(PropertyType p_type);
	void addProperty(PropertyPtr p_property);

		//PropertyPtr GetProperty(PropertyType p_type);
	template <typename T>
	void getProperty(T& p_value, PropertyType p_type) {
		PropertyPtr prop = m_properties[p_type];
		boost::shared_ptr<TProperty<T>> tmp = boost::shared_static_cast<TProperty<T>>(prop);
		p_value = tmp->GetValue();
	}

protected:
	std::map<PropertyType,PropertyPtr>  m_properties;
};

