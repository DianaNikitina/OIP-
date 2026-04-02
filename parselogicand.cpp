#include "language.h"

Value parse_logic_and(Parser* parser) 
{
    Value value = parse_comparison(parser);
    
    while (parser_match(parser, TOKEN_AND)) 
    {
        Value right = parse_comparison(parser);

        bool left_bool = false, right_bool = false;
        
        if (value.type == TYPE_BOOL) 
            left_bool = value.value.boolean;

        else if (value.type == TYPE_NUMBER) 
            left_bool = (value.value.number > EPS);

        else left_bool = false;
        
        if (right.type == TYPE_BOOL) 
            right_bool = right.value.boolean;

        else if (right.type == TYPE_NUMBER) 
            right_bool = (right.value.number > EPS);
            
        else right_bool = false;
        
        value = make_bool_value(left_bool && right_bool);
    }
    
    return value;
}