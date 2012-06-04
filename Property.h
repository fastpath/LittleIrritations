#pragma once
#include <string>
#include "PropertyType.h"
#include <boost/shared_ptr.hpp>

class Property;
typedef boost::shared_ptr<Property> PropertyPtr;

class Property
{
public:
	Property(PropertyType p_type);
	~Property(void);

	PropertyType GetType(void);
private:
	PropertyType m_type;
	
};

template <typename T>
class TProperty : public Property
{
public:
	TProperty(PropertyType p_type, T p_value) : Property(p_type)
	{
		m_value = boost::shared_ptr<T>(new T(p_value));
	}
	~TProperty(void) {}
	T GetValue(void) {return (*m_value); }
	boost::shared_ptr<T> GetValuePtr(void) {return m_value; }
private:
	boost::shared_ptr<T> m_value;
};

