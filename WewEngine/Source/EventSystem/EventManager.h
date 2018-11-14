#pragma once

#include "..\WewEngineStd.h"
#include "BaseEventData.h"

#include <cfloat>
#include <list>
#include <functional>

typedef std::function<void(IEventDataPtr)> EventListenerDelegate;

class IEventDispatcher
{
public:
    virtual bool AddListener(EventListenerDelegate& eventDelegate, const EventId& type) = 0;
    virtual bool RemoveListener(EventListenerDelegate eventDelegate, const EventId& type) = 0;

    virtual bool TriggerEventImmediately(const IEventDataPtr& eventData) = 0;

    virtual bool QueueEvent(const IEventDataPtr& eventData) = 0;
    virtual bool AbortEvent(const EventId& type, bool allOfType = false) = 0;

    virtual bool Update(float maxSeconds = FLT_MAX) = 0;
};

class EventDispatcher : IEventDispatcher
{
private:
    typedef std::list<EventListenerDelegate> EventListenerList;
    typedef std::map<EventId, EventListenerList> EventListenerMap;
    typedef std::list<IEventDataPtr> EventQueue;
    
    static constexpr int kEventDispatcherQueueCount = 2;

    EventListenerMap m_eventListeners;
    EventQueue m_queues[kEventDispatcherQueueCount];
    uint8_t m_activeQueue;

public:
    EventDispatcher();
    virtual ~EventDispatcher() {}

    // Inherited via IEventDispatcher
    virtual bool AddListener(EventListenerDelegate& eventDelegate, const EventId & type) override;
    virtual bool RemoveListener(EventListenerDelegate eventDelegate, const EventId & type) override;
    virtual bool TriggerEventImmediately(const IEventDataPtr & eventData) override;
    virtual bool QueueEvent(const IEventDataPtr & eventData) override;
    virtual bool AbortEvent(const EventId & type, bool allOfType = false) override;
    virtual bool Update(float maxSeconds = FLT_MAX) override;
};