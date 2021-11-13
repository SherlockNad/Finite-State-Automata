#include "StateManager.hpp"


void StateManager::addState(State state)
{
    SID_TYPE state_id = state.getId();
    
    if (!stateIsValid(state) || m_state_map.find(state_id) != m_state_map.end())
    {
        // Log error
    }
    m_state_map[state_id] = state;
    m_state_type_set.insert(state_id);
}

void StateManager::removeState(State state)
{
    SID_TYPE state_id = state.getId();
    
    if (!stateIsValid(state) || m_state_map.find(state_id) == m_state_map.end())
    {
        // Log error
    }
    m_state_map.erase(state.getId());
    m_state_type_set.erase(state_id);
}

State StateManager::getStateForSidType(SID_TYPE state_id)
{
    State ret_state;
    
    if (m_state_map.find(state_id) != m_state_map.end()) ret_state = m_state_map[state_id];
    
    return ret_state;
}

bool StateManager::stateIsValid(State &state)
{
    return state.getId() != INVALID_SID;
}

bool StateManager::hasSidType(SID_TYPE state_id)
{
    return (m_state_map.find(state_id) != m_state_map.end());
}

bool StateManager::hasState(State &state)
{
    SID_TYPE state_id = state.getId();
    if (m_state_map.find(state_id) == m_state_map.end()) return false;
    
    State present_state = m_state_map[state_id];
    return (present_state == state);
}

std::unordered_set<SID_TYPE> StateManager::getAllStateTypeList()
{
    return m_state_type_set;
}
