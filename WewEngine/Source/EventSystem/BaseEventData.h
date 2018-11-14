#pragma once

#include <memory>

class IEventData;
typedef std::shared_ptr<IEventData> IEventDataPtr;


class IEventData
{
    /////////////////////////////////////////////////
    // Enum Class
    /////////////////////////////////////////////////
public:
    enum class Id
    {
        Invalid = 0,
        ObjectCreated,
        ObjectDestroyed,
        Count
    };

public:
    virtual const Id GetEventType() const = 0;
    virtual float GetTimestamp() const = 0;
    virtual void Serialize(std::ostream& out) const = 0;
    virtual IEventDataPtr Copy() const = 0;
    virtual const char* GetName() const = 0;

};

typedef IEventData::Id EventId;



class BaseEventData : public IEventData
{
private:
    float m_timeStamp;

public:
    explicit BaseEventData(float timeStamp);
    virtual ~BaseEventData();

    // Inherited via IEventData
    virtual const IEventData::Id GetEventType() const override;
    virtual float GetTimestamp() const override;
    virtual void Serialize(std::ostream & out) const override;
    virtual IEventDataPtr Copy() const override;
    virtual const char * GetName() const override;
};

