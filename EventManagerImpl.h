#pragma once
#include "IBaseEventManager.h"
#include <map>

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;

class EventManagerImpl : public IBaseEventManager
{
	typedef std::list<EventListenerPtr> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<EventPtr> EventQueue;

	EventListenerMap m_eventListeners;
	EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
	int m_activeQueue; //this queue is actively processing, events will enque to the opposing queue


public:
	EventManagerImpl(const char* p_name, bool setAsGlobal);
	~EventManagerImpl(void);

	virtual bool VAddEventListener(const EventListenerPtr& p_listener, int p_typeCount, ...);
	virtual bool VRemoveEventListener(const EventListenerPtr& p_listener);
	virtual bool VAddEventTypeToListener(const EventListenerPtr& p_listener, const EventTypeList p_types);

	virtual bool VAddScriptEventListener(const EventListenerPtr& p_listener, const EventTypeList p_types);
	virtual bool VRemoveScriptEventListener(const EventListenerPtr& p_listener);
	
	virtual bool VProcessEvents(long p_time);
	virtual bool VTriggerEvent(EventPtr& p_event);
	virtual bool VQueueEvent(EventPtr& p_event);
	virtual bool VAbortEvent(const EventType& p_inType, bool p_allOfType);

	virtual bool VValidateType(EventType& p_type);

};

