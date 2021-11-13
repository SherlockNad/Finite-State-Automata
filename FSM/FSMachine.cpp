#include "FSMachine.h"

void FSMachine::start()
{
	m_event_processor.start();
    m_notification_handler.start();
}

void FSMachine::finish()
{
	m_finish = true;
	m_event_processor.finish();
    m_notification_handler.finish();
}

State FSMachine::getState()
{
    State curr_state;
    std::unique_lock<std::mutex> lck(mtx);
    curr_state = m_state;
    lck.unlock();
    return curr_state;
}

void FSMachine::SetState(State state)
{
    std::unique_lock<std::mutex> lck(mtx);
    m_state = state;
}

void FSMachine::handleEvent(Event &event)
{
    std::unique_lock<std::mutex> lck(mtx);
    if (m_mapper != nullptr)
    {
        if (m_mapper->eventIsValid(event))
        {
            State new_state = m_mapper->getStateForEventStateRelation(event, m_state);
            if (m_mapper->stateIsValid(new_state))
            {
                m_state = new_state;
                m_sQueue.push(m_state);
            }
            else
            {
                logError(INVALID_STATE, "Received invalid state on event: " + event.getDesc() + " and current_state: " + m_state.getDesc());
            }
        }
        else
        {
            logError(INVALID_EVENT, "Received invalid event: " + event.getDesc() + " when current_state is " + m_state.getDesc());
        }
    }
}

FSMachine::~FSMachine()
{
    m_finish = true;
    std::cout << "FSMachine::dtor called" << std::endl;
}
