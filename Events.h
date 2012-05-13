#pragma once
#include <boost/shared_ptr.hpp>
#include <map>
#include "EventType.h"
#include "Property.h"

class Event;
typedef boost::shared_ptr<Property> PropertyPtr;
typedef boost::shared_ptr<Event> EventPtr;


class Event
{
	const EventType m_type;
	const float m_timeStamp;

public:
	explicit Event( const EventType p_type, const float p_timeStamp = 0.0f) : m_timeStamp(p_timeStamp), m_type(p_type) { };
	~Event(void) { }

	const EventType& GetEventType(void) {return m_type; }
	float GetTimeStamp(void) const {return m_timeStamp; }

	bool HasProperty(PropertyType& p_type);
	void addProperty(PropertyPtr p_property);
	PropertyPtr GetProperty(PropertyType p_type);

private:
	std::map<PropertyType,PropertyPtr>  m_properties;

};

