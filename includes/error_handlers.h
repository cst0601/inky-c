#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

static inline int handle_error(
        const int response,
        const char* message,
        const char* file,
        const int line
        )
{
    if(response < 0)
    {
        printf("%d: %s in %s, line %d\n", response, message, file, line);
        exit(1);
    }
    return response;
}

#define HANDLE_ERROR(response, message) (handle_error (response, message, __FILE__, __LINE__))

#endif