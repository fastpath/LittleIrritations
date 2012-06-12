#include "IPropertyActor.h"


IPropertyActor::IPropertyActor(void)
{
}


IPropertyActor::~IPropertyActor(void)
{
}

bool IPropertyActor::hasProperty(PropertyType p_type)
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

void IPropertyActor::addProperty(PropertyPtr p_property)
{
	m_properties[p_property->GetType()] = p_property;
}
