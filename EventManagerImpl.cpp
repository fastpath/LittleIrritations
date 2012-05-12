#include "EventManagerImpl.h"

EventManagerImpl::EventManagerImpl(const char* p_name, bool p_setAsGlobal)
	: IBaseEventManager(p_name,p_setAsGlobal)
{
	m_activeQueue = 0;
}


EventManagerImpl::~EventManagerImpl(void)
{
	//
}

bool EventManagerImpl::VAddEventListener(const EventListenerPtr& p_listener, const EventTypeList p_types)
{
	for (auto itTypes = p_types.begin(); itTypes != p_types.end(); ++itTypes)
	{
		EventType currType = *itTypes;
		EventListenerList& eventListenerList = m_eventListeners[currType];
		for (auto itListener = eventListenerList.begin(); itListener != eventListenerList.end(); ++itListener)
		{
			if (p_listener == (*itListener))
			{
				//TODO add Log
				return false;
			}

			eventListenerList.push_back(p_listener);
		}
	}
	return true;
}

bool EventManagerImpl::VRemoveEventListener(const EventListenerPtr& p_listener) {
	//TODO log
	//No function to delete a Listener for a single EventType
	bool success = false;
	for (auto itMap = m_eventListeners.begin(); itMap != m_eventListeners.end(); ++itMap)
	{
		EventListenerList& listeners = (*itMap).second;
		for (auto itListener = listeners.begin(); itListener != listeners.end(); ++itListener)
		{
			if (p_listener == (*itListener)) {
				listeners.erase(itListener);
				success = true;
			}
		}
	}
	return success;	
}
	
bool EventManagerImpl::VProcessEvents(long p_time)
{
	//TODO ThreadSafeQueue

	//std::cout << "HAHAHA" << std::endl;

	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	while (!m_queues[queueToProcess].empty())
	{
		EventPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		//TODO Log Processing Event ...

		const EventType& eventType = pEvent->GetEventType();

		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;

			for (auto itListener = eventListeners.begin(); itListener != eventListeners.end(); ++itListener)
			{
				EventListenerPtr listener = (*itListener);
				listener->VprocessEvent(pEvent);
			}
		}
		// Time check
	}

	//If we couldn't process allEvents, we push them to the front of the new active queue
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!m_queues[queueToProcess].empty())
		{
			EventPtr pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}


bool EventManagerImpl::VTriggerEvent(EventPtr& p_event)
{
	//TODO log
	bool processed = false;
	auto findIt = m_eventListeners.find(p_event->GetEventType());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator itListener = eventListenerList.begin(); itListener != eventListenerList.end(); ++itListener)
		{
			EventListenerPtr listener = (*itListener);
			listener->VprocessEvent(p_event);
			processed = true;
		}
	}
	return processed;
}

bool EventManagerImpl::VQueueEvent(EventPtr& p_event) {
	if (m_activeQueue < 0 || m_activeQueue > EVENTMANAGER_NUM_QUEUES)
		return false; //BIG ERROR

	//std::cout << "Neues Event: " << EventTypeValueNames[p_event->GetEventType()] << std::endl;

	if (!p_event)
	{
		return false;
	}

	auto findIt = m_eventListeners.find(p_event->GetEventType());
	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(p_event);
		return true;
	}
	else
	{
		return false;
	}
}

bool EventManagerImpl::VAbortEvent(const EventType& p_inType, bool p_allOfType)
{
	if (m_activeQueue < 0 || m_activeQueue > EVENTMANAGER_NUM_QUEUES)
	return false; //BIG ERROR

	bool success = false;
	EventListenerMap::iterator findIt = m_eventListeners.find(p_inType);

	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto itEvent = eventQueue.begin();
		while (itEvent != eventQueue.end())
		{
			auto thisIt = itEvent;
			++itEvent;

			if ((*thisIt)->GetEventType() == p_inType)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!p_allOfType)
					break;
			}
		}
	}

	return success;
}

bool EventManagerImpl::VAddEventTypeToListener(const EventListenerPtr& p_listener, const EventTypeList p_types)
{
	return true;
}

bool EventManagerImpl::VAddScriptEventListener(const EventListenerPtr& p_listener, const EventTypeList p_types)
{
	return true;
}

bool EventManagerImpl::VRemoveScriptEventListener(const EventListenerPtr& p_listener)
{
	return true;
}

bool EventManagerImpl::VValidateType(EventType& p_type)
{
	return true;
}