#include "Property.h"


Property::Property(PropertyType p_type)
{
	m_type = p_type;
}

Property::~Property(void)
{
}

PropertyType Property::GetType(void)
{
	return m_type;
}


