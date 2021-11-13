#ifndef StateManager_hpp
#define StateManager_hpp

#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include "State.h"

class IStateManager
{
public:
    virtual void addState(State state) = 0;
    virtual void removeState(State state) = 0;
};

class StateManager: public IStateManager
{
    std::unordered_map<SID_TYPE, State> m_state_map;
    std::unordered_set<SID_TYPE> m_state_type_set;
    
public:
    virtual void addState(State state) override;
    virtual void removeState(State state) override;
    State getStateForSidType(SID_TYPE state_id);
    bool stateIsValid(State &state);
    bool hasSidType(SID_TYPE state_id);
    bool hasState(State &state);
    std::unordered_set<SID_TYPE> getAllStateTypeList();
};

#endif /* EventManager_hpp */
