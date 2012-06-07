#pragma once
#include <boost/shared_ptr.hpp>
#include <map>
#include "EventType.h"
#include "Property.h"

class Event;
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

	bool HasProperty(PropertyType p_type);
	void addProperty(PropertyPtr p_property);

	//PropertyPtr GetProperty(PropertyType p_type);
	template <typename T>
	void GetProperty(T& p_value, PropertyType p_type) {
		PropertyPtr prop = m_properties[p_type];
		boost::shared_ptr<TProperty<T>> tmp = boost::shared_static_cast<TProperty<T>>(prop);
		p_value = tmp->GetValue();
	}


private:
	std::map<PropertyType,PropertyPtr>  m_properties;

};

