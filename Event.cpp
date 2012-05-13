#pragma once

#include "Events.h"

bool Event::HasProperty(PropertyType& p_type)
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

void Event::addProperty(PropertyPtr p_property)
{
	m_properties[p_property->GetType()] = p_property;
}

PropertyPtr Event::GetProperty(PropertyType p_type)
{
	return m_properties[p_type];
}