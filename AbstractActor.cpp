#include "AbstractActor.h"


AbstractActor::AbstractActor(int p_id, ActorType p_type)
{
	m_id = p_id;
	m_type = p_type;
}


AbstractActor::~AbstractActor(void)
{
}

int AbstractActor::getId() {
	return m_id;
}

ActorType AbstractActor::getType()
{
	return m_type;
}

bool AbstractActor::hasProperty(PropertyType p_type)
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

void AbstractActor::addProperty(PropertyPtr p_property)
{
	m_properties[p_property->GetType()] = p_property;
}
