#include "../include/GramException.hpp"

GramException::GramException(std::string errorMessage)
{
    ErrorMessage = errorMessage;
}

GramException::~GramException()
{
}