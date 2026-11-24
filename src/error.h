#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define ERR(msg) fprintf(stderr, "Error: %s (%s:%d)\n", (msg), __FILE__, __LINE__);

#endif // ERROR_H
