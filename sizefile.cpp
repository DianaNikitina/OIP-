#include "language.h"

size_t sizeFile(FILE* file)
{
    assert(file);
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size_t(size);
}