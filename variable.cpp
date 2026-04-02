#include "language.h"

Variable* find_variable(Parser* parser, const char* name) 
{
    for (int i = 0; i < parser->var_count; i++) 
    {
        if (strcmp(parser->variables[i].name, name) == 0)
            return &parser->variables[i];
    }
    return NULL;
}

void set_variable(Parser* parser, const char* name, Value value) 
{
    Variable* var = find_variable(parser, name);
    if (var != NULL) 
    {
        if (var->value.type == TYPE_STRING && var->value.value.string != NULL)
            free(var->value.value.string);
        var->value = value;
    } 
    else 
    {
        if (parser->var_count < MAX_VARS) 
        {
            strcpy(parser->variables[parser->var_count].name, name);
            parser->variables[parser->var_count].value = value;
            parser->var_count++;
        } 
        else
            fprintf(stderr, "ERROR: a lot of variables\n");
    }
}