#pragma once
#include <boost/shared_ptr.hpp>
#include "ActorType.h"

class AbstractActor;
typedef boost::shared_ptr<AbstractActor> ActorPtr;

class AbstractActor
{
public:
	AbstractActor(int p_id, ActorType p_type);
	~AbstractActor(void);

	virtual void update(float dt) = 0;

	int getId();
	ActorType getType();

private:
	int m_id;
	ActorType m_type;
};

