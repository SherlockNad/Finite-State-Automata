#ifndef PRODUCER_H
#define PRODUCER_H

#include "FSMQueue.h"
#include "Event.h"

typedef unsigned int PRODID_TYPE;

class IProducer
{
public:
    virtual void publishEvent(Event event) = 0;
};

class Producer: public IProducer
{
    PRODID_TYPE m_id;
	FSMQueue<Event> &m_FSMQ;
public:
	Producer(PRODID_TYPE prod_id, FSMQueue<Event> &fsmQueue):
    m_id(prod_id),
	m_FSMQ(fsmQueue)
	{}
	virtual void publishEvent(Event event) override { m_FSMQ.push(event); }
	virtual ~Producer(){};
};


#endif //PRODUCER 
