#include "Producer.h"
#include "FSMachine.h"
#include "StateToSubsNotifier.hpp"

#include <iostream>

void simplePublish(FSMQueue<Event> &Q, EventManager *event_manager)
{
    Producer P(1, Q);
    P.publishEvent( event_manager->getEventForEidType(1) );
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void errorPublish(FSMQueue<Event> &Q, EventManager *event_manager)
{
    Producer P(0, Q);
    P.publishEvent( event_manager->getEventForEidType(0) );
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void complexPublish(FSMQueue<Event> &Q, EventManager *event_manager)
{
    for(int i = 1; i < 6; ++i)
    {
        Producer P(i, Q);
        P.publishEvent( event_manager->getEventForEidType(i) );
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void simple_test_case()
{
    FSMQueue<Event> Q;
    
    StateManager *state_manager = new StateManager();
    state_manager->addState(State(1, "Init"));
    state_manager->addState(State(2, "Created"));
    state_manager->addState(State(3, "Activated"));
    state_manager->addState(State(4, "Cancelled"));
    state_manager->addState(State(5, "InProgress"));
    state_manager->addState(State(6, "Completed"));
    
    EventManager *event_manager = new EventManager();
    event_manager->addEvent(Event(1, "FulFill Order"));
    event_manager->addEvent(Event(2, "Activate"));
    event_manager->addEvent(Event(3, "Cancel"));
    event_manager->addEvent(Event(4, "Make Progress"));
    event_manager->addEvent(Event(5, "Complete"));
    
    EventToStateMapper *mapper = new EventToStateMapper(state_manager, event_manager);
    mapper->addEventStateRelation(Event(1, "FulFill Order"), State(1, "Init"), State(2, "Created"));
    mapper->addEventStateRelation(Event(2, "Activate"), State(2, "Created"), State(3, "Activated"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(2, "Created"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(5, "InProgress"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(4, "Make Progress"), State(3, "Activated"), State(5, "InProgress"));
    mapper->addEventStateRelation(Event(5, "Complete"), State(5, "InProgress"), State(6, "Completed"));
    
    Subscriber* sub1 = new Subscriber(1);
    Subscriber* sub2 = new Subscriber(2);
    sub2->addState(State(2, "Created"));
    
    StateToSubsNotifier *notifier = new StateToSubsNotifier();
    notifier->subscribe(sub1);
    notifier->subscribe(sub2);
    
    FSMachine fsm(Q, notifier, mapper, State(1, "Init"));
    fsm.start();
    std::thread th(simplePublish, std::ref(Q), event_manager);
    th.join();
    
    notifier->unsubscribe(sub1);
    notifier->unsubscribe(sub2);
    delete notifier;
    
    delete sub1;
    delete sub2;
    
    delete mapper;
    delete event_manager;
    delete state_manager;
}

void error_test_case1()
{
    FSMQueue<Event> Q;
    
    StateManager *state_manager = new StateManager();
    state_manager->addState(State(1, "Init"));
    state_manager->addState(State(2, "Created"));
    state_manager->addState(State(3, "Activated"));
    state_manager->addState(State(4, "Cancelled"));
    state_manager->addState(State(5, "InProgress"));
    state_manager->addState(State(6, "Completed"));
    
    EventManager *event_manager = new EventManager();
    event_manager->addEvent(Event(1, "FulFill Order"));
    event_manager->addEvent(Event(2, "Activate"));
    event_manager->addEvent(Event(3, "Cancel"));
    event_manager->addEvent(Event(4, "Make Progress"));
    event_manager->addEvent(Event(5, "Complete"));
    
    EventToStateMapper *mapper = new EventToStateMapper(state_manager, event_manager);
    mapper->addEventStateRelation(Event(1, "FulFill Order"), State(1, "Init"), State(2, "Created"));
    mapper->addEventStateRelation(Event(2, "Activate"), State(2, "Created"), State(3, "Activated"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(2, "Created"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(5, "InProgress"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(4, "Make Progress"), State(3, "Activated"), State(5, "InProgress"));
    mapper->addEventStateRelation(Event(5, "Complete"), State(5, "InProgress"), State(6, "Completed"));
    
    Subscriber* sub1 = new Subscriber(1);
    Subscriber* sub2 = new Subscriber(2);
    sub2->addState(State(6, "Completed"));
    Subscriber* sub3 = new Subscriber(3);
    sub3->addState(State(4, "Cancelled"));
    
    StateToSubsNotifier *notifier = new StateToSubsNotifier();
    notifier->subscribe(sub1);
    notifier->subscribe(sub2);
    notifier->subscribe(sub3);
    
    FSMErrorLogger *logger = new FSMErrorLogger();
    FSMachine fsm(Q, notifier, mapper, State(1, "Init"));
    fsm.setErrorLogger(logger);
    fsm.start();
    std::thread th(errorPublish, std::ref(Q), event_manager);
    th.join();
    
    delete logger;
    
    notifier->unsubscribe(sub1);
    notifier->unsubscribe(sub2);
    notifier->unsubscribe(sub3);
    delete notifier;
    
    delete sub1;
    delete sub2;
    delete sub3;
    
    delete mapper;
    delete event_manager;
    delete state_manager;
}

void error_test_case2()
{
    FSMQueue<Event> Q;
    
    StateManager *state_manager = new StateManager();
    state_manager->addState(State(1, "Init"));
    state_manager->addState(State(2, "Created"));
    state_manager->addState(State(3, "Activated"));
    state_manager->addState(State(4, "Cancelled"));
    state_manager->addState(State(5, "InProgress"));
    state_manager->addState(State(6, "Completed"));
    
    EventManager *event_manager = new EventManager();
    event_manager->addEvent(Event(1, "FulFill Order"));
    event_manager->addEvent(Event(2, "Activate"));
    event_manager->addEvent(Event(3, "Cancel"));
    event_manager->addEvent(Event(4, "Make Progress"));
    event_manager->addEvent(Event(5, "Complete"));
    
    EventToStateMapper *mapper = new EventToStateMapper(state_manager, event_manager);
    mapper->addEventStateRelation(Event(1, "FulFill Order"), State(1, "Init"), State(2, "Created"));
    mapper->addEventStateRelation(Event(2, "Activate"), State(2, "Created"), State(3, "Activated"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(2, "Created"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(5, "InProgress"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(4, "Make Progress"), State(3, "Activated"), State(5, "InProgress"));
    mapper->addEventStateRelation(Event(5, "Complete"), State(5, "InProgress"), State(6, "Completed"));
    
    Subscriber* sub1 = new Subscriber(1);
    Subscriber* sub2 = new Subscriber(2);
    sub2->addState(State(6, "Completed"));
    Subscriber* sub3 = new Subscriber(3);
    sub3->addState(State(4, "Cancelled"));
    
    StateToSubsNotifier *notifier = new StateToSubsNotifier();
    notifier->subscribe(sub1);
    notifier->subscribe(sub2);
    notifier->subscribe(sub3);
    
    FSMErrorLogger *logger = new FSMErrorLogger();
    FSMachine fsm(Q, notifier, mapper, State(1, "Init"));
    fsm.setErrorLogger(logger);
    fsm.start();
    std::thread th(complexPublish, std::ref(Q), event_manager);
    th.join();
    
    delete logger;
    
    notifier->unsubscribe(sub1);
    notifier->unsubscribe(sub2);
    notifier->unsubscribe(sub3);
    delete notifier;
    
    delete sub1;
    delete sub2;
    delete sub3;
    
    delete mapper;
    delete event_manager;
    delete state_manager;
}

void complex_test_case()
{
    FSMQueue<Event> Q;
    
    StateManager *state_manager = new StateManager();
    state_manager->addState(State(1, "Init"));
    state_manager->addState(State(2, "Created"));
    state_manager->addState(State(3, "Activated"));
    state_manager->addState(State(4, "Cancelled"));
    state_manager->addState(State(5, "InProgress"));
    state_manager->addState(State(6, "Completed"));
    
    EventManager *event_manager = new EventManager();
    event_manager->addEvent(Event(1, "FulFill Order"));
    event_manager->addEvent(Event(2, "Activate"));
    event_manager->addEvent(Event(3, "Cancel"));
    event_manager->addEvent(Event(4, "Make Progress"));
    event_manager->addEvent(Event(5, "Complete"));
    
    EventToStateMapper *mapper = new EventToStateMapper(state_manager, event_manager);
    mapper->addEventStateRelation(Event(1, "FulFill Order"), State(1, "Init"), State(2, "Created"));
    mapper->addEventStateRelation(Event(2, "Activate"), State(2, "Created"), State(3, "Activated"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(2, "Created"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(3, "Cancel"), State(5, "InProgress"), State(4, "Cancelled"));
    mapper->addEventStateRelation(Event(4, "Make Progress"), State(3, "Activated"), State(5, "InProgress"));
    mapper->addEventStateRelation(Event(5, "Complete"), State(5, "InProgress"), State(6, "Completed"));
    mapper->addEventStateRelation(Event(5, "Complete"), State(5, "InProgress"), State(5, "InProgress"));
    
    Subscriber* sub1 = new Subscriber(1);
    Subscriber* sub2 = new Subscriber(2);
    sub2->addState(State(6, "Completed"));
    Subscriber* sub3 = new Subscriber(3);
    sub3->addState(State(4, "Cancelled"));
    
    StateToSubsNotifier *notifier = new StateToSubsNotifier();
    notifier->subscribe(sub1);
    notifier->subscribe(sub2);
    notifier->subscribe(sub3);
    
    FSMachine fsm(Q, notifier, mapper, State(4, "Cancelled"));
    fsm.start();
    std::thread th(complexPublish, std::ref(Q), event_manager);
    th.join();
    
    notifier->unsubscribe(sub1);
    notifier->unsubscribe(sub2);
    notifier->unsubscribe(sub3);
    delete notifier;
    
    delete sub1;
    delete sub2;
    delete sub3;
    
    delete mapper;
    delete event_manager;
    delete state_manager;
}

int main()
{
//    simple_test_case();
    
//    error_test_case1();
//
    error_test_case2();
//
//    complex_test_case();
    
	return 0;
}
