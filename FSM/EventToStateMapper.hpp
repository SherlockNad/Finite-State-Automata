#ifndef EventToStateMapper_hpp
#define EventToStateMapper_hpp

#include <stdio.h>
#include <unordered_map>
#include "Event.h"
#include "State.h"
#include "StateManager.hpp"
#include "EventManager.hpp"

class EventToStateMapper
{
    std::unordered_map<EID_TYPE, std::unordered_map<SID_TYPE, SID_TYPE> > m_event_to_state_mapper;
    StateManager* m_state_manager;
    EventManager* m_event_manager;
    std::unordered_map<SID_TYPE, int> m_state_edge_count_map;
public:
    EventToStateMapper(StateManager* state_manager, EventManager* event_manager):
    m_state_manager(state_manager),
    m_event_manager(event_manager)
    {}
    bool addEventStateRelation(EID_TYPE event_id, SID_TYPE fromState_id, SID_TYPE toState_id);
    bool addEventStateRelation(Event event, State fromState, State toState);
    
    State getStateForEventStateRelation(EID_TYPE event_id, SID_TYPE fromState_id);
    State getStateForEventStateRelation(Event event, State fromState);
    
    bool SidIsTerminal(SID_TYPE state_id);
    bool stateIsTerminal(State &state);
    
    bool eventIsValid(Event &event);
    bool hasEidType(EID_TYPE event_id);
    
    bool stateIsValid(State &state);
    bool hasSidType(SID_TYPE state_id);
    
};

#endif /* EventToStateMapper_hpp */
