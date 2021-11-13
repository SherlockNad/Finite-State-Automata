#ifndef FSMACHINE_H
#define FSMACHINE_H

#include "FSMQueue.h"
#include "Event.h"
#include "State.h"
#include "Subscriber.h"
#include "EventProcessor.h"
#include "NotificationHandler.h"
#include "EventToStateMapper.hpp"
#include "FSErrorLogger.hpp"
#include <iostream>

class IFSMachine
{
public:
    virtual void start() = 0;
    virtual void finish() = 0;
    virtual State getState() = 0;
    virtual void SetState(State state) = 0;
    virtual void handleEvent(Event &event) = 0;
};

class FSMachine: public IFSMachine
{
	FSMQueue<Event> &m_eQueue;
	FSMQueue<State> m_sQueue;
	EventProcessor m_event_processor;
    NotificationHandler m_notification_handler;
    EventToStateMapper *m_mapper;
    FSMErrorLogger *m_error_logger;
	bool m_finish;
	State m_state;
    std::mutex mtx;

    void logError(FSMErrorType error_type, std::string error_desc) { if (m_error_logger) m_error_logger->log(error_type, error_desc); }
    
public:
	FSMachine(FSMQueue<Event> &fsm_eQueue, StateToSubsNotifier *notifier, EventToStateMapper *mapper, State state):
	m_eQueue(fsm_eQueue),
	m_sQueue(),
    m_mapper(mapper),
	m_state(state),
	m_finish(false),
    m_error_logger(nullptr),
	m_event_processor(this, m_eQueue, m_sQueue, m_finish, m_state),
    m_notification_handler(notifier, m_sQueue)
	{
        std::cout << "FSMachine::ctor called" << std::endl;
    }

    bool isFinished() { return m_finish; }
    
	virtual void start() override;
	virtual void finish() override;
    
    virtual State getState() override;
    virtual void SetState(State state) override;
    virtual void handleEvent(Event &event) override;
    
    virtual void setErrorLogger(FSMErrorLogger *error_logger) { m_error_logger = error_logger; }

    // since dynamic subscribers are not required
//	virtual void addSubscriber(Subscriber *subscriber) {};
//	virtual void removeSubscriber(Subscriber *subscriber) {};

	virtual ~FSMachine();
};



#endif // FSMACHINE_H
