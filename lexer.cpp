#include "language.h"

char lexer_peek(Lexer* lexer) 
{
    return lexer->source[lexer->current];
}

char lexer_advance(Lexer* lexer) 
{
    lexer->current++;
    return lexer->source[lexer->current - 1];
}

bool lexer_is_at_end(Lexer* lexer) 
{
    return lexer_peek(lexer) == '\0';
}

void skip_whitespace(Lexer* lexer) 
{
    while (true) 
    {
        char c = lexer_peek(lexer);
        if (c == ' ' || c == '\t' || c == '\r') 
            lexer_advance(lexer);
        else if (c == '\n') 
        {
            lexer_advance(lexer);
            lexer->line++;
        } 
        else if (c == '#') 
        {
            while (lexer_peek(lexer) != '\n' && !lexer_is_at_end(lexer))
                lexer_advance(lexer);
        } 
        else
            break;
    }
}
