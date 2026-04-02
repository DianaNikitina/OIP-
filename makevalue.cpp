#include "language.h"

Value make_number_value(double num) 
{
    Value value;
    value.type = TYPE_NUMBER;
    value.value.number = num;
    return value;
}

Value make_string_value(const char* str) 
{
    Value value;
    value.type = TYPE_STRING;
    value.value.string = strdup(str);
    return value;
}

Value make_bool_value(bool b) 
{
    Value value;
    value.type = TYPE_BOOL;
    value.value.boolean = b;
    return value;
}

void value_print(Value value) 
{
    switch (value.type) 
    {
        case TYPE_NUMBER:
            printf("%g", value.value.number);
            break;
        case TYPE_STRING:
            printf("%s", value.value.string);
            break;
        case TYPE_BOOL:
            printf("%s", value.value.boolean ? "true" : "false");
            break;
        default:
            printf("undefined");
    }
}