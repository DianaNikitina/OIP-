#include "language.h"

int main() 
{
    FILE* file = fopen("language.txt", "r");
    size_t size_file = sizeFile(file);
    char* buffer = (char*) calloc(size_file, sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr, "ERROR calloc buffer\n");
        return 1;
    }
    printf("CORRECT calloc buffer\n");
    SECTION_SEPARATOR

    fread(buffer, size_file, sizeof(char), file);

    printf("Language\n");
    SECTION_SEPARATOR
    
    printf("programm\n");
    interpret(buffer);
    SECTION_SEPARATOR
    
    /*printf("str\n");
    interpret("name = \"World\"; print \"Hello \" + name + \"!\";");
    SECTION_SEPARATOR
    
    printf("logical operation\n");
    interpret("a = 10; b = 20; print a < b; print a == b;");
    SECTION_SEPARATOR
    
    printf("degree and remainder\n");
    interpret("print 2 ^ 3; print 17 % 5;");
    SECTION_SEPARATOR
    
    printf("bool\n");
    interpret("print true && false; print true || false; print !true;");
    SECTION_SEPARATOR
    
    printf("hard expression\n");
    interpret("x = 5; y = 3; z = (x + y) * 2; print z; print \"z = \" + z;");
    SECTION_SEPARATOR
    
    printf("prioritet operation\n");
    interpret("print 2 + 3 * 4 ^ 2;");
    SECTION_SEPARATOR
    
    printf("logical expression\n");
    interpret("print 1 && 0; print 5 || 0; print !0; print !1;");
    SECTION_SEPARATOR*/

    free(buffer);
    
    return 0;
}