#include "EventManager.h"

#include <assert.h>

#define SAME_DELEGATE(x, y) (x.target<void(IEventDataPtr)> == y.target<void(IEventDataPtr)>())

EventDispatcher::EventDispatcher()
    : m_activeQueue{ 0 }
{
}

bool EventDispatcher::AddListener(EventListenerDelegate& eventDelegate, const EventId & type)
{
    EventListenerList& listenerList = m_eventListeners[type];

#if _DEBUG
    for (auto listenerIt = listenerList.begin(); listenerIt != listenerList.end(); ++listenerIt)
    {
        auto target = eventDelegate.target<void(IEventDataPtr)>();
        assert(target != (*listenerIt).target<void(IEventDataPtr)>());
        //assert(SAME_DELEGATE(eventDelegate, (*listenerIt)));
    }
#endif

    listenerList.push_back(eventDelegate);

    return false;
}

bool EventDispatcher::RemoveListener(EventListenerDelegate eventDelegate, const EventId & type)
{
    bool sucess = false;

    auto listenerIt = m_eventListeners.find(type);
    if (listenerIt != m_eventListeners.end())
    {
        EventListenerList& listenerList = listenerIt->second;

        for (auto listIt = listenerList.begin(); listIt != listenerList.end(); ++listenerIt)
        {
            //if (SAME_DELEGATE((*listenerIt), ))
        }
    }
    return false;
}

bool EventDispatcher::TriggerEventImmediately(const IEventDataPtr & eventData)
{
    return false;
}

bool EventDispatcher::QueueEvent(const IEventDataPtr & eventData)
{
    return false;
}

bool EventDispatcher::AbortEvent(const EventId & type, bool allOfType)
{
    return false;
}

bool EventDispatcher::Update(float maxSeconds)
{
    return false;
}
