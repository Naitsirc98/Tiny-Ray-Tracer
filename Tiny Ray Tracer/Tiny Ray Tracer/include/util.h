#pragma once
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>

inline float randf()
{
	return ((float)rand()/(float)(RAND_MAX));
}
