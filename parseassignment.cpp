#include "language.h"

Value parse_assignment(Parser* parser) 
{
    if (parser->current.type == TOKEN_IDENTIFIER && peek_equals(parser->lexer)) 
    {
        char name[MAX_SYMBOL_LEN];
        strcpy(name, parser->current.lexeme);
        
        parser_advance(parser);  
        parser_advance(parser);
        
        Value value = parse_expression(parser);
        set_variable(parser, name, value);
        return value;
    }
    
    return parse_logic_or(parser);
}

Value parse_expression(Parser* parser) 
{
    return parse_assignment(parser);
}