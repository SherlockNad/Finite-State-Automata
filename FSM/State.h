#ifndef STATE_H
#define STATE_H

#include <string>

typedef unsigned int SID_TYPE;
#define INVALID_SID 0
#define INVALID_STATE_NAME "Invalid_State"
#define MAX_SID 100
#define ANY_SID MAX_SID

class State
{
	SID_TYPE m_id;
	std::string m_desc; 

public:
	State():
	m_id(INVALID_SID),
    m_desc(INVALID_STATE_NAME)
	{}
	State(SID_TYPE id, std::string desc):
	m_id(id),
	m_desc(desc)
	{}
    
    bool operator == (const State &state) const
    {
        return (m_id == state.getId() && m_desc == state.getDesc());
    }
    
	virtual SID_TYPE getId() const { return m_id; }
	virtual std::string getDesc() const { return m_desc; }
	virtual bool validId() { return m_id != INVALID_SID; }
	virtual ~State(){};
};


#endif //STATE_H 
