#pragma once
#include <boost/shared_ptr.hpp>
#include "IPropertyActor.h"
#include "ActorType.h"

class AbstractActor;
typedef boost::shared_ptr<AbstractActor> ActorPtr;

class AbstractActor : public IPropertyActor
{
public:
	AbstractActor(int p_id, ActorType p_type);
	~AbstractActor(void);

	virtual void Vupdate(float p_deltaMs) = 0;

	int getId();
	ActorType getType();

private:
	int m_id;
	ActorType m_type;
};

