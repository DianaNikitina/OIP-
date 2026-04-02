#include "language.h"

Value parse_power(Parser* parser) 
{
    Value value = parse_unary(parser);
    
    while (parser_match(parser, TOKEN_POW)) 
    {
        Value right = parse_unary(parser);
        if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
            value.value.number = pow(value.value.number, right.value.number);
        else
            fprintf(stderr, "ERROR: operation '^' do only with number\n");
    }
    
    return value;
}