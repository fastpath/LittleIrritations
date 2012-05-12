#pragma once
#include "IEventListener.h"
#include <list>

typedef std::list<EventType> EventTypeList;
typedef boost::shared_ptr<IEventListener> EventListenerPtr;

class IBaseEventManager
{
public:
	IBaseEventManager(const char* p_name, bool p_setAsGLobal);
	~IBaseEventManager(void);

	virtual bool VAddEventListener(const EventListenerPtr& p_listener, const EventTypeList p_types) = 0;
	virtual bool VRemoveEventListener(const EventListenerPtr& p_listener) = 0;
	virtual bool VAddEventTypeToListener(const EventListenerPtr& p_listener, const EventTypeList p_types) = 0;

	virtual bool VAddScriptEventListener(const EventListenerPtr& p_listener, const EventTypeList p_types) = 0;
	virtual bool VRemoveScriptEventListener(const EventListenerPtr& p_listener) = 0;
	
	virtual bool VProcessEvents(long p_time) = 0;
	virtual bool VTriggerEvent(EventPtr& p_event) = 0;
	virtual bool VQueueEvent(EventPtr& p_event) = 0;
	virtual bool VAbortEvent(const EventType& p_inType, bool p_allOfType) = 0;

	virtual bool VValidateType(EventType& p_type) = 0;

	static IBaseEventManager* Get(void);

};

