#include "Vector3f.h"
#include <math.h>

vec3* vec3_set(vec3* vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;

	return vec;
}

float vec3_length(const vec3* vec)
{
	return sqrt(vec3_sqrtlen(vec));
}

float vec3_sqrtlen(const vec3* vec)
{
	return vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
}


vec3* vec3_normalize(vec3* vec)
{
	return vec3_normalize_c(vec, vec);
}


vec3* vec3_normalize_c(const vec3* vec, vec3* dest)
{
	return vec3_divs_c(vec, vec3_length(vec), dest);
}


vec3* vec3_negate(vec3* vec)
{
	return vec3_negate_c(vec, vec);
}


vec3* vec3_negate_c(const vec3* vec, vec3* dest)
{
	return vec3_muls_c(vec, -1.0f, dest);
}


vec3* vec3_add(vec3* v1, const vec3* v2)
{
	return vec3_add_c(v1, v2, v1);
}


vec3* vec3_add_c(const vec3* v1, const vec3* v2, vec3* dest)
{
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;

	return dest;
}

vec3* vec3_adds(vec3* v1, float scalar)
{
	return vec3_adds_c(v1, scalar, v1);
}

vec3* vec3_adds_c(const vec3* v1, float scalar, vec3* dest)
{
	dest->x = v1->x + scalar;
	dest->y = v1->y + scalar;
	dest->z = v1->z + scalar;

	return dest;
}


vec3* vec3_sub(vec3* v1, const vec3* v2)
{
	return vec3_sub_c(v1, v2, v1);
}


vec3* vec3_sub_c(const vec3* v1, const vec3* v2, vec3* dest)
{
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	dest->z = v1->z - v2->z;

	return dest;
}

vec3* vec3_subs(vec3* v1, float scalar)
{
	return vec3_subs_c(v1, scalar, v1);
}

vec3* vec3_subs_c(const vec3* v1, float scalar, vec3* dest)
{
	dest->x = v1->x + scalar;
	dest->y = v1->y + scalar;
	dest->z = v1->z + scalar;

	return dest;
}


vec3* vec3_mul(vec3* v1, const vec3* v2)
{
	return vec3_mul_c(v1, v2, v1);
}


vec3* vec3_mul_c(const vec3* v1, const vec3* v2, vec3* dest)
{
	dest->x = v1->x* v2->x;
	dest->y = v1->y* v2->y;
	dest->z = v1->z* v2->z;

	return dest;
}


vec3* vec3_muls(vec3* v1, float scalar)
{
	return vec3_muls_c(v1, scalar, v1);
}


vec3* vec3_muls_c(const vec3* v1, float scalar, vec3* dest)
{
	dest->x = v1->x* scalar;
	dest->y = v1->y* scalar;
	dest->z = v1->z* scalar;

	return dest;
}


vec3* vec3_div(vec3* v1, const vec3* v2)
{
	return vec3_div_c(v1, v2, v1);
}


vec3* vec3_div_c(const vec3* v1, const vec3* v2, vec3* dest)
{
	dest->x = v1->x / v2->x;
	dest->y = v1->y / v2->y;
	dest->z = v1->z / v2->z;

	return dest;
}


vec3* vec3_divs(vec3* v1, float scalar) 
{
	return vec3_divs_c(v1, scalar, v1);
}


vec3* vec3_divs_c(const vec3* v1, float scalar, vec3* dest)
{
	dest->x = v1->x / scalar;
	dest->y = v1->y / scalar;
	dest->z = v1->z / scalar;

	return dest;
}


float vec3_dot(const vec3* v1, const vec3* v2)
{
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}


vec3* vec3_cross(vec3* v1, const vec3* v2)
{
	return vec3_cross_c(v1, v2, v1);
}


vec3* vec3_cross_c(const vec3* v1, const vec3* v2, vec3* dest)
{
	float x = v1->y* v2->z - v1->z* v2->y;
	float y = v1->x* v2->z - v1->z* v2->x;
	float z = v1->x* v2->y - v1->y* v2->x;

	return vec3_set(dest, x, y, z);
}