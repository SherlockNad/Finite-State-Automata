# Finite-State-Automata
A detailed system design based solution for Finite State Automate problem.

# Problem Statement
Implement a generic multi-threaded event driven finite state machine. 

A finite state machine is a system that can be in exactly one of a finite number of states at any given time. The FSM can change from one state to another in response to some external inputs. The change from one state to another is called a transition. An FSM is defined by a list of its states, its initial state, one or more terminal states and the conditions for each transition.

A finite-state machine (FSM) is event driven if the transition from one state to another is triggered by an event or a message.

A message/event can be sent by any registered message producer. Multiple subscribers should be able to register with the FSM. The FSM should change state on any valid message/event sent by a message producer. Any changes of state should be listened to by registered subscribers.
The FSM should be thread safe. Assume that all producers and subscribers of messages are on different threads.

A Subscriber should be able to listen on:
1. Successful transition to any of its interested states
2. Successful transition to any state

The FSM should have the following capabilities:
1. Has one Start State and multiple end states
2. Easy way to define states and transitions between states
3. Validate State machine constructed
4. Error handling in case of invalid state transitions


Sample State Machine diagram:

![Sample State Machine diagram](https://github.com/nadeem2376/Finite-State-Automata/blob/main/FSM_example.png)

Sample Happy testcase: FSM in Created state and Activate Event Occurs, changes the current state to Activated.

Sample Error Test case: FSM in Activated State and Activate Event occurs, appropriate error handling to be supported.

Design requirements:
- Guidelines.
- Please use structures provided by the language of your choice. 
- Please provide a basic set of test cases to validate the solution.
- Adding new States and transitions should be as simple as possible.
- You can hardcode the subscriptions. No need to implement dynamic subscription (ability to add subscribers at runtime).
- Everything needs to be implemented in a single process.

# Solution

Things implemented in this design solution:
- Running code
- Functional completeness
- Application of OO design principles
- Separation of concerns
- Domain abstractions
- Testability
- Code readability
- Support for concurrency
- Language proficiency
- Error handling 
- Extensibility

## Solution system design:

![Solution system design](https://github.com/nadeem2376/Finite-State-Automata/blob/main/FSM_workflow.png)

## Classes and responsibilities

### IFSMachine
Interface which defines basic functionalities of a FSMachine

### FSMachine
Concrete implementation of IFSMachine. Main class which provides initial set of FSM capabilities

### Event
This is the basic class representing an event by its name and id.

### EventManager
This class implements IEventManager. Along with that, it has these following responsibilities:
- Manages or keep track of events.
- answer all type of event related queries.

### EventProcessor
This acts as a watcher on top of event/state queues and pass on those events to the associated component for further processing

### EventToStateMapper
This is simply a mapper who keeps track of event states

### FSErrorLogger
Basic class to log errors across different workflows

### FSMQueue
Qeueu class which acts as a transitioanry buffer for events to be pushed and popped

### FSMQueueSubscriber
Interface for those clients who wants to subscribe to a FSMQueue and listen to event updates

### NotificationHandler
Concrete implementation of FSMQueueSubscriber which handles the event updates and pass on the info to the appropriate component.

### Producer
This is the creator of events with just a basic method of """publishEvent"""

### State
Class to represent state of an event

### StateManager
Class to manage addition and removal of states. Along with that, it has these following responsibilities:
- Manages or keep track of states.
- answer all type of state related queries.


### StateToSubsNotifier
Class to manage subscribers for different event states

### Subscriber
Class to represent a listener to a particular state change and manage what all states it listens to.




# build and run
To build and run FSM project, use command:
```
make target
```

Once target executable is created, run ./target to run the program


To clean object files, use command:
```
make clean
```

There are 4 test-cases implemented in the main function:
1. simple_test_case() : simple producer and subscriber workflow
2. error_test_case1() : invalid event error handling
3. error_test_case2() : invalid state error handling
4. complex_test_case() : A complex case with multiple producers and subscribers

By default, complex_test_case() is enabled in main. One can simply uncomment the other test_case(s) to see their outputs as well.

A workflow diagram is also attached to better describe the workflow and responsibilities of different components involved.

# Contribute

If you have suggestions for how this app could be improved, or want to report a bug, open an issue! I'd love all and any contributions.

# License

This project is licensed under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)







