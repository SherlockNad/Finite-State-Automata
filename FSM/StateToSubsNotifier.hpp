//
//  StateToSubsMapper.hpp
//  FSM
//
//  Created by Md Nadeem Akhtar on 13/08/21.
//

#ifndef StateToSubsNotifier_hpp
#define StateToSubsNotifier_hpp

#include <stdio.h>
#include <unordered_set>
#include <unordered_map>
#include "Subscriber.h"

class IStateToSubsNotifier
{
public:
    virtual void subscribe(Subscriber *subs) = 0;
    virtual void unsubscribe(Subscriber *subs) = 0;
};

class StateToSubsNotifier: public IStateToSubsNotifier
{
    std::unordered_set<Subscriber *> m_all_state_subs_list;
    std::unordered_map<SID_TYPE, std::unordered_set<Subscriber *> > m_spec_state_to_subs_mapper;
    
    void notifyAllSubsInSet(std::unordered_set<Subscriber *> &subs_set, const State &state);
    
public:
    virtual void subscribe(Subscriber *subs) override;
    virtual void unsubscribe(Subscriber *subs) override;
    
    virtual void notifyAllSubsWithChangedState(const State &state);
};

#endif /* StateToSubsNotifier_hpp */
