#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef unsigned int SUBSID_TYPE;

#include "State.h"
#include <iostream>
#include <unordered_set>

/*
 Assumption: Subscriber with no specific state list is interested in all state change
 **/

class ISubscriber
{
public:
    virtual void addState(State state) = 0;
    virtual void handleStateChangedTo(const State &state) = 0;
};

class Subscriber: public ISubscriber
{
	SUBSID_TYPE m_id;
    std::unordered_set<SID_TYPE> m_state_list;
public:
	Subscriber(SUBSID_TYPE id):
	m_id(id),
    m_state_list()
	{}
	Subscriber(SUBSID_TYPE id, std::unordered_set<SID_TYPE> &state_list):
	m_id(id),
	m_state_list(state_list)
	{}
    
    virtual void addState(State state) override { if (state.validId()) m_state_list.insert(state.getId()); }
    virtual std::unordered_set<SID_TYPE> getStateList() { return m_state_list; }
    virtual void handleStateChangedTo(const State &state) override { std::cout << "Subscriber: " << m_id << " received state : " << state.getDesc() << std::endl; }

	virtual ~Subscriber(){};
};

#endif //SUBSCRIBER_H
