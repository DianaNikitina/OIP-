#include "language.h"

bool is_digit(char c) 
{ 
    return c >= '0' && c <= '9'; 
}

bool is_alpha(char c) 
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; 
}

bool is_alnum(char c) 
{ 
    return is_alpha(c) || is_digit(c); 
}