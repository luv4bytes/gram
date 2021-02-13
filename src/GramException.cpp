#include "../include/GramException.hpp"

GramException::GramException(std::string errorMessage) throw()
{
    ErrorMessage = errorMessage;
}

GramException::~GramException()
{
}