#pragma once
#include "Hitable.h"

typedef struct HitableList
{
	HitFunction hit;
	Hitable** list;
	unsigned int size;
} HitableList;

/* Creates a HitableList with the given parameters */
HitableList hlist_create(Hitable** list, unsigned int size);