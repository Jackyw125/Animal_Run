#ifndef VEC_IN_H
#define VEC_IN_H
#include <osbind.h>
typedef void (*Vector)();

Vector install_vector(int num, Vector vector);

#endif