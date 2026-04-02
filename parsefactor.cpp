#include "language.h"

Value parse_factor(Parser* parser) 
{
    Value value = parse_power(parser);
    
    while (true) 
    {
        if (parser_match(parser, TOKEN_MUL)) 
        {
            Value right = parse_power(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value.value.number *= right.value.number;
            else
                fprintf(stderr, "ERROR: operation '*' do only with number\n");
        } 
        else if (parser_match(parser, TOKEN_DIV)) 
        {
            Value right = parse_power(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER) 
            {
                if (right.value.number > EPS)
                    value.value.number /= right.value.number;
                else
                    fprintf(stderr, "ERROR: division on 0\n");
            } 
            else
                fprintf(stderr, "ERROR: operation '/' do only with number\n");
        } 
        else if (parser_match(parser, TOKEN_MOD)) 
        {
            Value right = parse_power(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value.value.number = fmod(value.value.number, right.value.number);
            else
                fprintf(stderr, "ERROR: operation '%%' do only with number\n");
        } 
        else
            break;
    }
    
    return value;
}