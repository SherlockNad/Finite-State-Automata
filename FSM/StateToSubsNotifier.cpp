#include "StateToSubsNotifier.hpp"

void StateToSubsNotifier::notifyAllSubsInSet(std::unordered_set<Subscriber *> &subs_set, const State &state)
{
    for(Subscriber* subs: subs_set)
    {
        if (subs != nullptr) subs->handleStateChangedTo(state);
    }
}

void StateToSubsNotifier::subscribe(Subscriber *subs)
{
    if (subs == nullptr) return;
    
    std::unordered_set<SID_TYPE> subs_state_list = subs->getStateList();
    
    if (subs_state_list.size() == 0)
    {
        m_all_state_subs_list.insert(subs);
        return;
    }
    
    for(auto state_id: subs_state_list)
    {
        if (m_spec_state_to_subs_mapper.find(state_id) == m_spec_state_to_subs_mapper.end())
        {
            m_spec_state_to_subs_mapper[state_id] = std::unordered_set<Subscriber *>();
        }
        m_spec_state_to_subs_mapper[state_id].insert(subs);
    }
    
}

void StateToSubsNotifier::unsubscribe(Subscriber *subs)
{
    if (subs == nullptr) return;
    
    m_all_state_subs_list.erase(subs);
    
    std::unordered_set<SID_TYPE> subs_state_list = subs->getStateList();
    
    if (subs_state_list.size() != 0)
    {
        for(SID_TYPE state_id: subs_state_list)
        {
            if (m_spec_state_to_subs_mapper.find(state_id) != m_spec_state_to_subs_mapper.end())
            {
                m_spec_state_to_subs_mapper[state_id].erase(subs);
            }
        }
    }
}

void StateToSubsNotifier::notifyAllSubsWithChangedState(const State &state)
{
    notifyAllSubsInSet(m_all_state_subs_list, state);
    
    SID_TYPE state_id = state.getId();
    
    if (m_spec_state_to_subs_mapper.find(state_id) != m_spec_state_to_subs_mapper.end())
    {
        std::unordered_set<Subscriber *> &subs_set = m_spec_state_to_subs_mapper[state_id];
        
        notifyAllSubsInSet(subs_set, state);
    }
}


