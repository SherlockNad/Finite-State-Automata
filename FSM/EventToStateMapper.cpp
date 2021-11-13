#include "EventToStateMapper.hpp"

bool EventToStateMapper::addEventStateRelation(EID_TYPE event_id, SID_TYPE fromState_id, SID_TYPE toState_id)
{
    if (m_event_manager == nullptr || m_state_manager == nullptr) return false;
    if (!m_event_manager->hasEidType(event_id) || !m_state_manager->hasSidType(fromState_id) || !m_state_manager->hasSidType(toState_id)) return false;
    if (fromState_id == toState_id) return false;
    bool ret_val = true;
    if (m_event_to_state_mapper.find(event_id) == m_event_to_state_mapper.end())
    {
        m_event_to_state_mapper[event_id] = std::unordered_map<SID_TYPE, SID_TYPE>();
        m_event_to_state_mapper[event_id][fromState_id] = toState_id;
        m_state_edge_count_map[fromState_id]++;
    }
    else
    {
        std::unordered_map<SID_TYPE, SID_TYPE> &s_map = m_event_to_state_mapper[event_id];
        if (s_map.find(fromState_id) != s_map.end())
        {
            ret_val = (s_map[fromState_id] == toState_id);
        }
        else
        {
            s_map[fromState_id] = toState_id;
        }
    }
    
    return ret_val;
}


bool EventToStateMapper::addEventStateRelation(Event event, State fromState, State toState)
{
    return addEventStateRelation(event.getId(), fromState.getId(), toState.getId());
}

State EventToStateMapper::getStateForEventStateRelation(EID_TYPE event_id, SID_TYPE fromState_id)
{
    State ret_state;
    if (m_state_manager == nullptr || m_event_manager == nullptr) return ret_state;
    
    if (m_event_to_state_mapper.find(event_id) != m_event_to_state_mapper.end())
    {
        std::unordered_map<SID_TYPE, SID_TYPE> &s_map = m_event_to_state_mapper[event_id];
        if (s_map.find(fromState_id) != s_map.end())
        {
            ret_state = m_state_manager->getStateForSidType(s_map[fromState_id]);
        }
    }
    
    return ret_state;
}

State EventToStateMapper::getStateForEventStateRelation(Event event, State fromState)
{
    return getStateForEventStateRelation(event.getId(), fromState.getId());
}

bool EventToStateMapper::SidIsTerminal(SID_TYPE state_id)
{
    if (m_state_manager == nullptr || !m_state_manager->hasSidType(state_id)) return false;
    int state_id_edge_count = 0;
    if (m_state_edge_count_map.find(state_id) != m_state_edge_count_map.end())
    {
        state_id_edge_count = m_state_edge_count_map[state_id];
    }
    
    return (state_id_edge_count == 0);
}

bool EventToStateMapper::stateIsTerminal(State &state)
{
    return SidIsTerminal(state.getId());
}

bool EventToStateMapper::eventIsValid(Event &event)
{
    if (m_event_manager == nullptr) return false;
    return m_event_manager->eventIsValid(event);
}

bool EventToStateMapper::hasEidType(EID_TYPE event_id)
{
    if (m_event_manager == nullptr) return false;
    return m_event_manager->hasEidType(event_id);
}

bool EventToStateMapper::stateIsValid(State &state)
{
    if (m_state_manager == nullptr) return false;
    return m_state_manager->stateIsValid(state);
}

bool EventToStateMapper::hasSidType(SID_TYPE state_id)
{
    if (m_state_manager == nullptr) return false;
    return m_state_manager->hasSidType(state_id);
}
