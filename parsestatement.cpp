#include "language.h"

void parse_statement(Parser* parser) 
{
    if (parser_match(parser, TOKEN_PRINT)) 
    {
        Value value = parse_expression(parser);
        value_print(value);
        printf("\n");
        
        if (!parser_match(parser, TOKEN_SEMICOLON))
            fprintf(stderr, "ERROR: expected ';' after print\n");
    } 
    else 
    {
        parse_expression(parser);
        if (!parser_match(parser, TOKEN_SEMICOLON))
            fprintf(stderr, "ERROR: expected ';' after expression\n");
    }
}

void parse_program(Parser* parser) 
{
    while (!parser_match(parser, TOKEN_EOF))
        parse_statement(parser);
}
