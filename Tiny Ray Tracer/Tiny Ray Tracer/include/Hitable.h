#pragma once
#include "Ray.h"

#define TRUE 1
#define FALSE 0

typedef struct HitRecord
{
	float t;
	Vec3 p;
	Vec3 normal;
} HitRecord;

typedef int(*HitFunction)(void*, const Ray*, float, float, HitRecord*);

typedef struct Hitable
{
	HitFunction hit;
} Hitable;

/* Creates a default HitRecord */
HitRecord hrecord_create();