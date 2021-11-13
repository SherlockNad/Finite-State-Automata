#ifndef NOTIFICATION_HANDLER_H
#define NOTIFICATION_HANDLER_H

#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>
#include "FSMQueue.h"
#include "Event.h"
#include "State.h"
#include <iostream>

class FSMachine;
class StateToSubsNotifier;

class NotificationHandler: public QueueSubscriber
{
public:
    FSMQueue<State> &m_shared_sQueue;
    std::mutex mtx;
    std::condition_variable m_con_v;
    std::future<bool> m_processor;
    bool m_finish;
    StateToSubsNotifier* m_notifier;
    
    NotificationHandler(StateToSubsNotifier *notifier, FSMQueue<State> &fsm_sQueue):
    m_notifier(notifier),
    m_shared_sQueue(fsm_sQueue),
    m_finish(false)
    {
        std::cout << "NotificationHandler::ctor called" << std::endl;
    }
    
    virtual void start();
    virtual void finish();

    virtual bool continueNotificationHandling();
    virtual bool startNotificationHandling();
    
    virtual void handleQueueEvent(QueueEvent q_event) override;

    virtual ~NotificationHandler();
};

#endif // NOTIFICATION_HANDLER_H
