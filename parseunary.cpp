#include "language.h"

Value parse_unary(Parser* parser) 
{
    if (parser_match(parser, TOKEN_MINUS)) 
    {
        Value right = parse_unary(parser);
        if (right.type == TYPE_NUMBER)
            right.value.number = -right.value.number;
        return right;
    }
    
    if (parser_match(parser, TOKEN_NOT)) 
    {
        Value right = parse_unary(parser);
        if (right.type == TYPE_BOOL)
            right.value.boolean = !right.value.boolean;
        else if (right.type == TYPE_NUMBER) 
        {
            right.type = TYPE_BOOL;
            right.value.boolean = (right.value.number < EPS);
        }
        return right;
    }
    
    if (parser_match(parser, TOKEN_PLUS))
        return parse_unary(parser);
    
    return parse_primary(parser);
}