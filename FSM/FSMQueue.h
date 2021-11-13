#ifndef FSMQUEUE_H
#define FSMQUEUE_H

#include <mutex>
#include <queue>
#include <set>
#include <iostream>

enum class QueueEvent
{
    POP,
    PUSH,
    NONE
};

class QueueSubscriber
{
public:
    virtual void handleQueueEvent(QueueEvent q_event) = 0;
};

template <typename T>
class FSMQueue
{
	std::mutex mtx;
	std::queue<T> Q;
    std::set<QueueSubscriber *> subs_set;
    
    void notify_all(QueueEvent q_event)
    {
        for(auto it = subs_set.begin(); it != subs_set.end(); ++it)
        {
            QueueSubscriber* curr_subs = *it;
            if (curr_subs != nullptr) curr_subs->handleQueueEvent(q_event);
        }
    }
    
public:
	void pop()
	{
		std::unique_lock<std::mutex> lck(mtx);
		if (!Q.empty())
        {
            Q.pop();
//            std::cout << "Item popped to Queue" << std::endl;
            notify_all(QueueEvent::POP);
        }
        
	}
	void push(T elem)
	{
		std::unique_lock<std::mutex> lck(mtx);
		Q.push(elem);
//        std::cout << "Item pushed to Queue" << std::endl;
        notify_all(QueueEvent::PUSH);
	}
	T front()
	{
		T top_elem;
		std::unique_lock<std::mutex> lck(mtx);
		if (!Q.empty()) top_elem = Q.front();
		lck.unlock();
		return top_elem;
	}
	bool empty()
	{
		bool is_empty = true;
		std::unique_lock<std::mutex> lck(mtx);
		is_empty = Q.empty();
		lck.unlock();
		return is_empty;
	}
    size_t size()
    {
        size_t q_size;
        std::unique_lock<std::mutex> lck(mtx);
        q_size = Q.size();
        lck.unlock();
        return q_size;
    }
    
    void subscribe(QueueSubscriber *queue_subs)
    {
        std::unique_lock<std::mutex> lck(mtx);
        if (queue_subs != nullptr)
            subs_set.insert(queue_subs);
    }
    
    void unsubscribe(QueueSubscriber *queue_subs)
    {
        std::unique_lock<std::mutex> lck(mtx);
        if (queue_subs != nullptr)
            subs_set.insert(queue_subs);
    }
    
	virtual ~FSMQueue(){};
};



#endif //FSMQUEUE 
