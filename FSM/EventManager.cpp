#include "EventManager.hpp"


void EventManager::addEvent(Event event)
{
    EID_TYPE event_id = event.getId();
    
    if (!eventIsValid(event) || m_event_map.find(event_id) != m_event_map.end())
    {
        // Log error
    }
    m_event_map[event_id] = event;
    m_event_type_set.insert(event_id);
}

void EventManager::removeEvent(Event event)
{
    EID_TYPE event_id = event.getId();
    
    if (!eventIsValid(event) || m_event_map.find(event_id) == m_event_map.end())
    {
        // Log error
    }
    m_event_map.erase(event.getId());
    m_event_type_set.erase(event_id);
}

Event EventManager::getEventForEidType(EID_TYPE event_id)
{
    Event ret_event;
    
    if (m_event_map.find(event_id) != m_event_map.end()) ret_event = m_event_map[event_id];
    
    return ret_event;
}

bool EventManager::eventIsValid(Event &event)
{
    return event.getId() != INVALID_EID;
}

bool EventManager::hasEidType(EID_TYPE event_id)
{
    return (m_event_map.find(event_id) != m_event_map.end());
}

bool EventManager::hasEvent(Event &event)
{
    EID_TYPE event_id = event.getId();
    if (m_event_map.find(event_id) == m_event_map.end()) return false;
    
    Event present_event = m_event_map[event_id];
    return (present_event == event);
}

std::unordered_set<EID_TYPE> EventManager::getAllEventTypeList()
{
    return m_event_type_set;
}

