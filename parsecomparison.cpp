#include "language.h"

Value parse_comparison(Parser* parser) 
{
    Value value = parse_term(parser);
    
    while (true) 
    {
        if (parser_match(parser, TOKEN_EQEQ)) 
        {
            Value right = parse_term(parser);
            bool result = false;
            
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                result = (value.value.number - right.value.number < EPS);

            else if (value.type == TYPE_BOOL && right.type == TYPE_BOOL)
                result = (value.value.boolean == right.value.boolean);

            else if (value.type == TYPE_STRING && right.type == TYPE_STRING)
                result = (strcmp(value.value.string, right.value.string) == 0);

            else if (value.type != right.type)
                result = false;
            
            value = make_bool_value(result);
        } 
        else if (parser_match(parser, TOKEN_NEQ)) 
        {
            Value right = parse_term(parser);
            bool result = false;
            
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                result = (value.value.number - right.value.number > EPS);

            else if (value.type == TYPE_BOOL && right.type == TYPE_BOOL)
                result = (value.value.boolean != right.value.boolean);

            else if (value.type == TYPE_STRING && right.type == TYPE_STRING)
                result = (strcmp(value.value.string, right.value.string) != 0);

            else if (value.type != right.type)
                result = true;
            
            value = make_bool_value(result);
        } 
        else if (parser_match(parser, TOKEN_LT)) 
        {
            Value right = parse_term(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value = make_bool_value(value.value.number < right.value.number);

            else
                fprintf(stderr, "ERROR: operation '<' do only with number\n");
        } 
        else if (parser_match(parser, TOKEN_GT)) 
        {
            Value right = parse_term(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value = make_bool_value(value.value.number > right.value.number);

            else
                fprintf(stderr, "ERROR: operation '>' do only with number\n");

        } 
        else if (parser_match(parser, TOKEN_LEQ)) 
        {
            Value right = parse_term(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value = make_bool_value(value.value.number <= right.value.number);
            else
                fprintf(stderr, "ERROR: operation '<=' do only with number\n");

        } 
        else if (parser_match(parser, TOKEN_GEQ)) 
        {
            Value right = parse_term(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value = make_bool_value(value.value.number >= right.value.number);
            else
                fprintf(stderr, "ERROR: operation '>=' do only with number\n");
        } 
        else
            break;
    }
    
    return value;
}