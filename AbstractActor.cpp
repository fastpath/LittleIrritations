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
