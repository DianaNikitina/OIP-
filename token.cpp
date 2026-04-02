#include "language.h"

Token make_token(TokenType type, const char* lexeme) 
{
    Token token = {TOKEN_NONE, {0}, 0.0, NULL};
    token.type = type;
    strncpy(token.lexeme, lexeme, MAX_SYMBOL_LEN - 1);
    token.lexeme[MAX_SYMBOL_LEN - 1] = '\0';
    token.string_value = NULL;
    return token;
}

Token make_number_token(double value) 
{
    Token token;
    token.type = TOKEN_NUMBER;
    token.number_value = value;
    sprintf(token.lexeme, "%g", value);
    token.string_value = NULL;
    return token;
}

Token make_string_token(const char* value) 
{
    Token token;
    token.type = TOKEN_STRING;
    token.string_value = strdup(value);
    sprintf(token.lexeme, "\"%s\"", value);
    return token;
}

TokenType check_keyword(const char* text) 
{
    if (strcmp(text, "if") == 0) return TOKEN_IF;
    if (strcmp(text, "else") == 0) return TOKEN_ELSE;
    if (strcmp(text, "while") == 0) return TOKEN_WHILE;
    if (strcmp(text, "for") == 0) return TOKEN_FOR;
    if (strcmp(text, "func") == 0) return TOKEN_FUNC;
    if (strcmp(text, "return") == 0) return TOKEN_RETURN;
    if (strcmp(text, "print") == 0) return TOKEN_PRINT;
    if (strcmp(text, "true") == 0) return TOKEN_TRUE;
    if (strcmp(text, "false") == 0) return TOKEN_FALSE;
    return TOKEN_IDENTIFIER;
}

Token lexer_next_token(Lexer* lexer) 
{
    skip_whitespace(lexer);
    
    if (lexer_is_at_end(lexer))
        return make_token(TOKEN_EOF, "");
    
    char c = lexer_advance(lexer);
    
    if (is_digit(c)) 
    {
        char num_str[32];
        int pos = 0;
        num_str[pos++] = c;
        
        while (is_digit(lexer_peek(lexer)) || lexer_peek(lexer) == '.') 
            num_str[pos++] = lexer_advance(lexer);
            
        num_str[pos] = '\0';
        
        return make_number_token(atof(num_str));
    }
    
    if (is_alpha(c)) 
    {
        char ident[MAX_SYMBOL_LEN];
        int pos = 0;
        ident[pos++] = c;
        
        while (is_alnum(lexer_peek(lexer)))
            ident[pos++] = lexer_advance(lexer);

        ident[pos] = '\0';
        
        TokenType type = check_keyword(ident);
        if (type == TOKEN_IDENTIFIER)
            return make_token(type, ident);
        else 
        {
            Token token;
            token.type = type;
            strcpy(token.lexeme, ident);
            token.string_value = NULL;
            return token;
        }
    }

    if (c == '"') 
    {
        char str_val[256];
        int pos = 0;
        
        while (lexer_peek(lexer) != '"' && !lexer_is_at_end(lexer))
            str_val[pos++] = lexer_advance(lexer);
        
        if (lexer_is_at_end(lexer)) 
        {
            fprintf(stderr, "ERROR: do not close string\n");
            return make_token(TOKEN_EOF, "");
        }
        
        lexer_advance(lexer);
        str_val[pos] = '\0';
        
        return make_string_token(str_val);
    }
    
    switch (c) 
    {
        case '+': return make_token(TOKEN_PLUS, "+");
        case '-': return make_token(TOKEN_MINUS, "-");
        case '*': return make_token(TOKEN_MUL, "*");
        case '/': return make_token(TOKEN_DIV, "/");
        case '%': return make_token(TOKEN_MOD, "%");
        case '^': return make_token(TOKEN_POW, "^");
        case '(': return make_token(TOKEN_LPAREN, "(");
        case ')': return make_token(TOKEN_RPAREN, ")");
        case '{': return make_token(TOKEN_LBRACE, "{");
        case '}': return make_token(TOKEN_RBRACE, "}");
        case ',': return make_token(TOKEN_COMMA, ",");
        case ';': return make_token(TOKEN_SEMICOLON, ";");
        case ':': return make_token(TOKEN_COLON, ":");
        case '!':
            if (lexer_peek(lexer) == '=') 
            {
                lexer_advance(lexer);
                return make_token(TOKEN_NEQ, "!=");
            }
            return make_token(TOKEN_NOT, "!");
        case '=':
            if (lexer_peek(lexer) == '=') 
            {
                lexer_advance(lexer);
                return make_token(TOKEN_EQEQ, "==");
            }
            return make_token(TOKEN_EQ, "=");
        case '<':
            if (lexer_peek(lexer) == '=') 
            {
                lexer_advance(lexer);
                return make_token(TOKEN_LEQ, "<=");
            }
            return make_token(TOKEN_LT, "<");
        case '>':
            if (lexer_peek(lexer) == '=') 
            {
                lexer_advance(lexer);
                return make_token(TOKEN_GEQ, ">=");
            }
            return make_token(TOKEN_GT, ">");
        case '&':
            if (lexer_peek(lexer) == '&') 
            {
                lexer_advance(lexer);
                return make_token(TOKEN_AND, "&&");
            }
            break;
        case '|':
            if (lexer_peek(lexer) == '|') 
            {
                lexer_advance(lexer);
                return make_token(TOKEN_OR, "||");
            }
            break;
        default:
            break;
    }
    
    fprintf(stderr, "ERROR: lexer found unfamous sign - '%c'\n", c);
    return make_token(TOKEN_EOF, "");
}