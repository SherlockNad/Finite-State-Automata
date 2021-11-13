#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include "Event.h"

class IEventManager
{
public:
    virtual void addEvent(Event event) = 0;
    virtual void removeEvent(Event event) = 0;
};

class EventManager: public IEventManager
{
    std::unordered_map<EID_TYPE, Event> m_event_map;
    std::unordered_set<EID_TYPE> m_event_type_set;
    
public:
    virtual void addEvent(Event event) override;
    virtual void removeEvent(Event event) override;
    Event getEventForEidType(EID_TYPE event_id);
    bool eventIsValid(Event &event);
    bool hasEidType(EID_TYPE event_id);
    bool hasEvent(Event &event);
    std::unordered_set<EID_TYPE> getAllEventTypeList();
};

#endif /* EventManager_hpp */
