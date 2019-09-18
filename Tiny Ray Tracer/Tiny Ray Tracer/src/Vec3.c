#include "Vec3.h"
#include <math.h>


Vec3 vec3_create(float x, float y, float z)
{
	return (Vec3) {x, y, z};
}

Vec3 vec3_create_val(float xyz)
{
	return vec3_create(xyz, xyz, xyz);
}

Vec3* vec3_set(Vec3* vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;

	return vec;
}

float vec3_length(const Vec3* vec)
{
	return sqrt(vec3_sqrtlen(vec));
}

float vec3_sqrtlen(const Vec3* vec)
{
	return vec->x*vec->x + vec->y*vec->y + vec->z*vec->z;
}


Vec3* vec3_normalize(Vec3* vec)
{
	return vec3_normalize_c(vec, vec);
}


Vec3* vec3_normalize_c(const Vec3* vec, Vec3* dest)
{
	return vec3_divs_c(vec, vec3_length(vec), dest);
}


Vec3* vec3_negate(Vec3* vec)
{
	return vec3_negate_c(vec, vec);
}


Vec3* vec3_negate_c(const Vec3* vec, Vec3* dest)
{
	return vec3_muls_c(vec, -1.0f, dest);
}


Vec3* vec3_add(Vec3* v1, const Vec3* v2)
{
	return vec3_add_c(v1, v2, v1);
}


Vec3* vec3_add_c(const Vec3* v1, const Vec3* v2, Vec3* dest)
{
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;

	return dest;
}

Vec3* vec3_adds(Vec3* v1, float scalar)
{
	return vec3_adds_c(v1, scalar, v1);
}

Vec3* vec3_adds_c(const Vec3* v1, float scalar, Vec3* dest)
{
	dest->x = v1->x + scalar;
	dest->y = v1->y + scalar;
	dest->z = v1->z + scalar;

	return dest;
}


Vec3* vec3_sub(Vec3* v1, const Vec3* v2)
{
	return vec3_sub_c(v1, v2, v1);
}


Vec3* vec3_sub_c(const Vec3* v1, const Vec3* v2, Vec3* dest)
{
	dest->x = v1->x - v2->x;
	dest->y = v1->y - v2->y;
	dest->z = v1->z - v2->z;

	return dest;
}

Vec3* vec3_subs(Vec3* v1, float scalar)
{
	return vec3_subs_c(v1, scalar, v1);
}

Vec3* vec3_subs_c(const Vec3* v1, float scalar, Vec3* dest)
{
	dest->x = v1->x + scalar;
	dest->y = v1->y + scalar;
	dest->z = v1->z + scalar;

	return dest;
}


Vec3* vec3_mul(Vec3* v1, const Vec3* v2)
{
	return vec3_mul_c(v1, v2, v1);
}


Vec3* vec3_mul_c(const Vec3* v1, const Vec3* v2, Vec3* dest)
{
	dest->x = v1->x * v2->x;
	dest->y = v1->y * v2->y;
	dest->z = v1->z * v2->z;

	return dest;
}


Vec3* vec3_muls(Vec3* v1, float scalar)
{
	return vec3_muls_c(v1, scalar, v1);
}


Vec3* vec3_muls_c(const Vec3* v1, float scalar, Vec3* dest)
{
	dest->x = v1->x * scalar;
	dest->y = v1->y * scalar;
	dest->z = v1->z * scalar;

	return dest;
}


Vec3* vec3_div(Vec3* v1, const Vec3* v2)
{
	return vec3_div_c(v1, v2, v1);
}


Vec3* vec3_div_c(const Vec3* v1, const Vec3* v2, Vec3* dest)
{
	dest->x = v1->x / v2->x;
	dest->y = v1->y / v2->y;
	dest->z = v1->z / v2->z;

	return dest;
}


Vec3* vec3_divs(Vec3* v1, float scalar) 
{
	return vec3_divs_c(v1, scalar, v1);
}


Vec3* vec3_divs_c(const Vec3* v1, float scalar, Vec3* dest)
{
	dest->x = v1->x / scalar;
	dest->y = v1->y / scalar;
	dest->z = v1->z / scalar;

	return dest;
}


float vec3_dot(const Vec3* v1, const Vec3* v2)
{
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}


Vec3* vec3_cross(Vec3* v1, const Vec3* v2)
{
	return vec3_cross_c(v1, v2, v1);
}


Vec3* vec3_cross_c(const Vec3* v1, const Vec3* v2, Vec3* dest)
{
	float x = v1->y * v2->z - v1->z * v2->y;
	float y = v1->x * v2->z - v1->z * v2->x;
	float z = v1->x * v2->y - v1->y * v2->x;

	return vec3_set(dest, x, y, z);
}

Vec3 vec3_copy(const Vec3* src)
{
	return (Vec3) {src->x, src->y, src->z};
}

Vec3* vec3_copy_to(const Vec3* src, Vec3* dest)
{
	return vec3_set(dest, src->x, src->y, src->z);
}
