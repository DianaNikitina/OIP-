#include "language.h"

Value parse_primary(Parser* parser) 
{
    if (parser_match(parser, TOKEN_NUMBER))
        return make_number_value(parser->previous.number_value);
    
    if (parser_match(parser, TOKEN_STRING))
        return make_string_value(parser->previous.string_value);
    
    if (parser_match(parser, TOKEN_TRUE))
        return make_bool_value(true);
    
    if (parser_match(parser, TOKEN_FALSE))
        return make_bool_value(false);
    
    if (parser_match(parser, TOKEN_IDENTIFIER)) 
    {
        char* name = parser->previous.lexeme;
        Variable* var = find_variable(parser, name);
        if (var != NULL)
            return var->value;
        else 
        {
            fprintf(stderr, "ERROR: variable '%s' not defined\n", name);
            return make_number_value(0);
        }
    }
    
    if (parser_match(parser, TOKEN_LPAREN)) 
    {
        Value value = parse_expression(parser);
        if (!parser_match(parser, TOKEN_RPAREN))
            fprintf(stderr, "ERROR: expected ')'\n");
        return value;
    }
    
    fprintf(stderr, "Ошибка: ожидается выражение\n");
    return make_number_value(0);
}