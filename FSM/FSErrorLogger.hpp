#ifndef FSErrorLogger_hpp
#define FSErrorLogger_hpp

#include <stdio.h>
#include <string>
#include <iostream>

template <typename T>
class IErrorLogger
{
public:
    virtual void log(T error_type, std::string error_desc) = 0;
};

enum FSMErrorType
{
    INVALID_EVENT,
    INVALID_STATE,
    NONE,
    ERROR_NUM
};

static const char* FSMErrorName[FSMErrorType::ERROR_NUM] = {"InValid_Event", "Invalid_State", "None"};

class FSMErrorLogger: public IErrorLogger<FSMErrorType>
{
public:
    virtual void log(FSMErrorType error_type, std::string error_desc)
    { std::cout << "error_type: " << FSMErrorName[error_type] << " :: error_desc: " << error_desc << std::endl; }
};


#endif /* FSLogger_hpp */
