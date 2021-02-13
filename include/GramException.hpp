#ifndef NETEXCEPTION_H
#define NETEXCEPTION_H

#include <string>

class GramException : public std::exception
{

public:
    GramException(std::string errorMessage) throw();
    ~GramException();

    std::string ErrorMessage;
};

#endif