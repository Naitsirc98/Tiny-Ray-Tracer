#pragma once
#include "Ray.h"

#define TRUE 1
#define FALSE 0

typedef struct Material Material;
typedef struct Hitable Hitable;

typedef struct HitRecord
{
	float t;
	Vec3 p;
	Vec3 normal;
	Material* material;
} HitRecord;

typedef int(*HitFunction)(void*, const Ray*, float, float, HitRecord*);
typedef void(*FreeFunction)(Hitable*);

typedef struct Hitable
{
	HitFunction hit;
	FreeFunction free;
} Hitable;


