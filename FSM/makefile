CC=g++
CFLAGS=-std=c++11

target: main.o EventManager.o EventProcessor.o EventToStateMapper.o FSErrorLogger.o FSMachine.o NotificationHandler.o StateManager.o StateToSubsNotifier.o
	$(CC) $(CFLAGS) -o target main.o EventManager.o EventProcessor.o EventToStateMapper.o FSErrorLogger.o FSMachine.o NotificationHandler.o StateManager.o StateToSubsNotifier.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

EventProcessor.o: EventProcessor.cpp
	$(CC) $(CFLAGS) -c EventProcessor.cpp

EventToStateMapper.o: EventToStateMapper.cpp
	$(CC) $(CFLAGS) -c EventToStateMapper.cpp

FSErrorLogger.o: FSErrorLogger.cpp
	$(CC) $(CFLAGS) -c FSErrorLogger.cpp

FSMachine.o: FSMachine.cpp
	$(CC) $(CFLAGS) -c FSMachine.cpp

NotificationHandler.o: NotificationHandler.cpp
	$(CC) $(CFLAGS) -c NotificationHandler.cpp

StateManager.o: StateManager.cpp
	$(CC) $(CFLAGS) -c StateManager.cpp

StateToSubsNotifier.o: StateToSubsNotifier.cpp
	$(CC) $(CFLAGS) -c StateToSubsNotifier.cpp

clean: 
	$(RM) count *.o *~