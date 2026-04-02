#include "language.h"

bool peek_equals(Lexer* lexer) 
{
    int saved_pos = lexer->current;
    int saved_line = lexer->line;
    
    skip_whitespace(lexer);
    bool result = (lexer_peek(lexer) == '=');
    
    lexer->current = saved_pos;
    lexer->line = saved_line;
    return result;
}