#ifndef LANGUAGE_H_INCLUDED
#define LANGUAGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <cassert>

#define MAX_VARS 100
#define MAX_FUNCS 50
#define MAX_SYMBOL_LEN 32
#define MAX_CODE_LINES 1000
#define STACK_SIZE 1000
#define SECTION_SEPARATOR printf("-----------------\n\n");
const double EPS = 1e-9;


typedef enum 
{
    TYPE_NONE,
    TYPE_NUMBER,
    TYPE_STRING,
    TYPE_BOOL
} ValueType;

typedef struct 
{
    ValueType type;
    union 
    {
        double number;
        char* string;
        bool boolean;
    } value;
} Value;

typedef struct 
{
    char name[MAX_SYMBOL_LEN];
    Value value;
} Variable;


typedef enum 
{
    TOKEN_NONE,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_PLUS,        
    TOKEN_MINUS,       
    TOKEN_MUL,         
    TOKEN_DIV,         
    TOKEN_MOD,         
    TOKEN_POW,         
    TOKEN_EQ,          
    TOKEN_EQEQ,        
    TOKEN_NEQ,         
    TOKEN_LT,          
    TOKEN_GT,          
    TOKEN_LEQ,         
    TOKEN_GEQ,         
    TOKEN_AND,         
    TOKEN_OR,          
    TOKEN_NOT,         
    TOKEN_LPAREN,      
    TOKEN_RPAREN,      
    TOKEN_LBRACE,      
    TOKEN_RBRACE,      
    TOKEN_COMMA,       
    TOKEN_SEMICOLON,   
    TOKEN_COLON,       
    TOKEN_IF,          
    TOKEN_ELSE,        
    TOKEN_WHILE,       
    TOKEN_FOR,         
    TOKEN_FUNC,        
    TOKEN_RETURN,      
    TOKEN_PRINT,       
    TOKEN_TRUE,        
    TOKEN_FALSE,       
    TOKEN_EOF          
} TokenType;

typedef struct 
{
    TokenType type;
    char lexeme[MAX_SYMBOL_LEN];
    double number_value;
    char* string_value;
} Token;


typedef struct 
{
    const char* source;
    int current;
    int line;
} Lexer;

typedef struct 
{
    Lexer* lexer;
    Token current;
    Token previous;
    
    Variable variables[MAX_VARS];
    int var_count;
    
    Value stack[STACK_SIZE];
    int stack_ptr;
} Parser;

bool is_digit(char c);
bool is_alpha(char c);
bool is_alnum(char c);
char lexer_peek(Lexer* lexer);
char lexer_advance(Lexer* lexer);
bool lexer_is_at_end(Lexer* lexer);
void skip_whitespace(Lexer* lexer);
Token make_token(TokenType type, const char* lexeme);
Token make_number_token(double value);
Token make_string_token(const char* value);
TokenType check_keyword(const char* text);
Token lexer_next_token(Lexer* lexer);
void parser_init(Parser* parser, const char* source);
void parser_advance(Parser* parser);
bool parser_check(Parser* parser, TokenType type);
bool parser_match(Parser* parser, TokenType type);
Value make_number_value(double num);
Value make_string_value(const char* str);
Value make_bool_value(bool b);
void value_print(Value value);
Variable* find_variable(Parser* parser, const char* name);
void set_variable(Parser* parser, const char* name, Value value);
Value parse_expression(Parser* parser);
Value parse_primary(Parser* parser);
Value parse_unary(Parser* parser);
Value parse_power(Parser* parser);
Value parse_factor(Parser* parser);
Value parse_term(Parser* parser);
Value parse_comparison(Parser* parser);
Value parse_logic_and(Parser* parser);
Value parse_logic_or(Parser* parser);
Value parse_assignment(Parser* parser);
void parse_statement(Parser* parser);
void parse_program(Parser* parser);
void interpret(char* source);  
bool peek_equals(Lexer* lexer); 
size_t sizeFile(FILE* file);  
#endif