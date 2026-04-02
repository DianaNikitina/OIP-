#include "language.h"

void interpret(char* source) 
{
    Parser parser = {0};
    parser_init(&parser, source);
    parse_program(&parser);
    
    free(parser.lexer);
}