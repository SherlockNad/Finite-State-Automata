#ifndef EVENT_PROCESSOR_H
#define EVENT_PROCESSOR_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>
#include "FSMQueue.h"
#include "Event.h"
#include "State.h"
#include <iostream>

class FSMachine;

class EventProcessor: public QueueSubscriber
{
public:
    FSMQueue<Event> &m_shared_eQueue;
    FSMQueue<State> &m_shared_sQueue;
    std::mutex mtx;
    std::condition_variable m_con_v;
    std::future<bool> m_processor;
    bool m_finish;
    FSMachine* m_fsm;
    
	EventProcessor(FSMachine* fsm, FSMQueue<Event> &fsm_eQueue, FSMQueue<State> &fsm_sQueue, bool &shared_finish, State &shared_state):
    m_fsm(fsm),
	m_shared_eQueue(fsm_eQueue),
	m_shared_sQueue(fsm_sQueue),
    m_finish(false)
	{
        std::cout << "EventProcessor::ctor called" << std::endl;
    }
//    EventProcessor()
//    {}
    
	virtual void start();
	virtual void finish();

    virtual bool continueEventProcessing();
    virtual bool startEventProcessing();
    
    virtual void handleQueueEvent(QueueEvent q_event) override;

	virtual ~EventProcessor();
};

#endif // EVENT_PROCESSOR_H
