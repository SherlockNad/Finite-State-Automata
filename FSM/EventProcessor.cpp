#include "EventProcessor.h"
#include "FSMachine.h"
#include <chrono>

bool EventProcessor::startEventProcessing()
{
    while(!m_finish)
    {
        std::cout << "Event processing continued!!" << std::endl;
        
        std::unique_lock<std::mutex> lck(mtx);
        m_con_v.wait(lck, [this]() { return continueEventProcessing(); });
        
        std::cout << "Event Queue current size : " << m_shared_eQueue.size() << std::endl;
        
        while(!m_shared_eQueue.empty())
        {
            Event top_event = m_shared_eQueue.front();
            m_shared_eQueue.pop();
            std::cout << "Current event processing : " << top_event.getDesc() << std::endl;
            State curr_state = m_fsm->getState();
            std::cout << "Current FSM state : " << curr_state.getId() << std::endl;
            m_fsm->handleEvent(top_event);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    
    std::cout << "Event processing completed" << std::endl;
    return true;
}

void EventProcessor::start()
{
    m_shared_eQueue.subscribe(this);
    m_processor = std::async(std::launch::async, &EventProcessor::startEventProcessing, this);
}

bool EventProcessor::continueEventProcessing()
{
    bool continue_processing = m_shared_eQueue.empty() && !m_finish;
//    std::cout << "Continue processing : " << continue_processing << std::endl;
	return !continue_processing;
}

void EventProcessor::finish()
{
    m_shared_eQueue.unsubscribe(this);
    m_finish = true;
    m_con_v.notify_all();
    
    if(m_processor.valid())
        m_processor.wait();
}

void EventProcessor::handleQueueEvent(QueueEvent q_event)
{
    if (q_event == QueueEvent::PUSH) m_con_v.notify_all();
}

EventProcessor::~EventProcessor()
{
    finish();
    std::cout << "EventProcessor::dtor called" << std::endl;
}


