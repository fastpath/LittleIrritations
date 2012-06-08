#pragma once
#include <boost/shared_ptr.hpp>
#include <map>
#include "Property.h"
#include "ActorType.h"

class AbstractActor;
typedef boost::shared_ptr<AbstractActor> ActorPtr;

class AbstractActor
{
public:
	AbstractActor(int p_id, ActorType p_type);
	~AbstractActor(void);

	virtual void Vupdate(float p_deltaMs) = 0;

	int getId();
	ActorType getType();
	void addProperty(PropertyPtr p_property);
	bool hasProperty(PropertyType& p_type);

	template <typename T>
	void GetProperty(T& value, PropertyType p_type) {
		PropertyPtr prop = m_properties[p_type];
		boost::shared_ptr<TProperty<T>> tmp = boost::shared_static_cast<TProperty<T>>(prop);
		value = tmp->GetValue();
	}

private:
	int m_id;
	ActorType m_type;
	std::map<PropertyType,PropertyPtr> m_properties;
};

