#pragma once
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include <memory.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ALLOC_NEW(type, count) (type*)malloc(count * sizeof(type));

inline float randf()
{
	return ((float)rand()/(float)(RAND_MAX));
}
