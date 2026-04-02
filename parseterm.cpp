#include "language.h"

Value parse_term(Parser* parser) 
{
    Value value = parse_factor(parser);
    
    while (true) 
    {
        if (parser_match(parser, TOKEN_PLUS)) 
        {
            Value right = parse_factor(parser);

            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value.value.number += right.value.number;

            else if (value.type == TYPE_STRING || right.type == TYPE_STRING) 
            {
                char result[256] = {0};
                char left_str[128] = {0}, right_str[128] = {0};
                
                if (value.type == TYPE_NUMBER)
                    sprintf(left_str, "%g", value.value.number);

                else if (value.type == TYPE_STRING)
                    strcpy(left_str, value.value.string);

                else if (value.type == TYPE_BOOL)
                    strcpy(left_str, value.value.boolean ? "true" : "false");

                else
                    strcpy(left_str, "?");
                
                if (right.type == TYPE_NUMBER)
                    sprintf(right_str, "%g", right.value.number);

                else if (right.type == TYPE_STRING)
                    strcpy(right_str, right.value.string);

                else if (right.type == TYPE_BOOL)
                    strcpy(right_str, right.value.boolean ? "true" : "false");

                else
                    strcpy(right_str, "?");
                
                sprintf(result, "%s%s", left_str, right_str);

                if (value.type == TYPE_STRING && value.value.string != NULL)
                    free(value.value.string);

                value = make_string_value(result);
            }

            else if (value.type == TYPE_BOOL && right.type == TYPE_BOOL)
                value = make_number_value((value.value.boolean ? 1 : 0) + (right.value.boolean ? 1 : 0));

        } 
        else if (parser_match(parser, TOKEN_MINUS)) 
        {
            Value right = parse_factor(parser);
            if (value.type == TYPE_NUMBER && right.type == TYPE_NUMBER)
                value.value.number -= right.value.number;

            else if (value.type == TYPE_BOOL && right.type == TYPE_BOOL)
                value = make_number_value((value.value.boolean ? 1 : 0) - (right.value.boolean ? 1 : 0));

            else
                fprintf(stderr, "ERROR: operation '-' do only with number\n");
        } 
        else
            break;
    }
    
    return value;
}