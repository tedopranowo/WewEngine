#include "BaseEventData.h"

BaseEventData::BaseEventData(float timeStamp)
    : m_timeStamp(timeStamp)
{
}

const IEventData::Id BaseEventData::GetEventType() const
{
    // TODO: insert return statement here
    return IEventData::Id::Invalid;
}

float BaseEventData::GetTimestamp() const
{
    return 0.0f;
}

void BaseEventData::Serialize(std::ostream & out) const
{
}

IEventDataPtr BaseEventData::Copy() const
{
    return IEventDataPtr();
}

const char * BaseEventData::GetName() const
{
    return nullptr;
}
