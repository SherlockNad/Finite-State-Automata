#ifndef EVENT_H
#define EVENT_H

#include <string>

typedef unsigned int EID_TYPE;
#define INVALID_EID 0
#define INVALID_EVENT_NAME "Invalid_Event"

class Event
{
	EID_TYPE m_id;
	std::string m_desc; 

public:
	Event():
	m_id(INVALID_EID),
    m_desc(INVALID_EVENT_NAME)
	{}
	Event(EID_TYPE id, std::string desc):
	m_id(id),
	m_desc(desc)
	{}
    
    bool operator == (const Event &event)
    {
        return (m_id == event.getId() && m_desc == event.getDesc());
    }
    
	virtual EID_TYPE getId() const { return m_id; }
	virtual std::string getDesc() const { return m_desc; }
	virtual bool validId() { return m_id != INVALID_EID; }
	virtual ~Event(){};
};


#endif //EVENT_H 
