#pragma once
#include "EventType.h"
#include "IPropertyActor.h"

class Event;
typedef boost::shared_ptr<Event> EventPtr;


class Event : public IPropertyActor
{
	const EventType m_type;
	const float m_timeStamp;

public:
	explicit Event( const EventType p_type, const float p_timeStamp = 0.0f) : m_timeStamp(p_timeStamp), m_type(p_type) { };
	~Event(void) { }

	const EventType& GetEventType(void) {return m_type; }
	float GetTimeStamp(void) const {return m_timeStamp; }
};

