#pragma once
#include "Events.h"
#include <boost/shared_ptr.hpp>

class IEventListener
{
public:
	IEventListener(void);
	~IEventListener(void);

	virtual bool VprocessEvent(EventPtr p_event) = 0;
};

