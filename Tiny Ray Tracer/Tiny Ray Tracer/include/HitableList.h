#pragma once
#include "Hitable.h"

typedef struct HitableList
{
	HitFunction hit;
	FreeFunction free;
	Hitable** list;
	unsigned int size;
} HitableList;

/* Creates a HitableList with the given parameters */
HitableList hlist_create(Hitable** list, unsigned int size);
/* Creates a HitableList dinamically. The returned pointer must be freed */
HitableList* hlist_new(unsigned int size);
/* Creates a HitableList dinamically with the given dinamically allocated list. The returned pointer must be freed */
HitableList* hlist_newl(Hitable** list, unsigned int size);
/* Frees the memory used by the given HitableList */
void hlist_free(HitableList* hlist);