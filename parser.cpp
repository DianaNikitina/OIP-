#include "language.h"

void parser_init(Parser* parser, const char* source) 
{
    Lexer* lexer = (Lexer*)calloc(1, sizeof(Lexer));
    lexer->source = source;
    lexer->current = 0;
    lexer->line = 1;
    
    parser->lexer = lexer;
    parser->var_count = 0;
    parser->stack_ptr = 0;
    
    parser->current = lexer_next_token(lexer);
}

void parser_advance(Parser* parser) 
{
    parser->previous = parser->current;
    parser->current = lexer_next_token(parser->lexer);
}

bool parser_check(Parser* parser, TokenType type) 
{
    return parser->current.type == type;
}

bool parser_match(Parser* parser, TokenType type) 
{
    if (parser_check(parser, type)) 
    {
        parser_advance(parser);
        return true;
    }
    return false;
}