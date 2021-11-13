#include "NotificationHandler.h"
#include "FSMachine.h"
#include "StateToSubsNotifier.hpp"
#include <chrono>

bool NotificationHandler::startNotificationHandling()
{
    while(!m_finish)
    {
        std::cout << "State processing continued!!" << std::endl;
        
        std::unique_lock<std::mutex> lck(mtx);
        m_con_v.wait(lck, [this]() { return continueNotificationHandling(); });
        
        std::cout << "State Queue current size : " << m_shared_sQueue.size() << std::endl;
        
        while(!m_shared_sQueue.empty())
        {
            State top_state = m_shared_sQueue.front();
            m_shared_sQueue.pop();
            std::cout << "Current state processing : " << top_state.getDesc() << std::endl;
            if (m_notifier) m_notifier->notifyAllSubsWithChangedState(top_state);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

    }
    
    std::cout << "Notification handling completed" << std::endl;
    return true;
}

void NotificationHandler::start()
{
    m_shared_sQueue.subscribe(this);
    m_processor = std::async(std::launch::async, &NotificationHandler::startNotificationHandling, this);
}

bool NotificationHandler::continueNotificationHandling()
{
    bool continue_processing = m_shared_sQueue.empty() && !m_finish;
//    std::cout << "Continue notification handling : " << continue_processing << std::endl;
    return !continue_processing;
}

void NotificationHandler::finish()
{
    m_shared_sQueue.unsubscribe(this);
    m_finish = true;
    m_con_v.notify_all();
    
    if(m_processor.valid())
        m_processor.wait();
}

void NotificationHandler::handleQueueEvent(QueueEvent q_event)
{
    if (q_event == QueueEvent::PUSH) m_con_v.notify_all();
}

NotificationHandler::~NotificationHandler()
{
    finish();
    std::cout << "NotificationHandler::dtor called" << std::endl;
}


