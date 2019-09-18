#pragma once

typedef struct Vector3f
{
	union
	{
		struct
		{
			float x, y, z;
		};

		struct
		{
			float r, g, b;
		};

		float data[3];
	};
} vec3;

/* Set all components of this vector to the given values*/
vec3* vec3_set(vec3* vec, float x, float y, float z);
/* Returns the length of the given vector*/
float vec3_length(const vec3* vec);
/* Returns the squared length of the given vector*/
float vec3_sqrtlen(const vec3* vec);
/* Normalizes the given vector*/
vec3* vec3_normalize(vec3* vec);
/* Normalizes the given vector and stores the result in dest*/
vec3* vec3_normalize_c(const vec3* vec, vec3* dest);
/* Negates the given vector*/
vec3* vec3_negate(vec3* vec);
/* Negates the given vector and stores the result in dest*/
vec3* vec3_negate_c(const vec3* vec, vec3* dest);
/* Add v2 to v1 and returns it*/
vec3* vec3_add(vec3* v1, const vec3* v2);
/* Add v2 to v1 and stores the result in dest*/
vec3* vec3_add_c(const vec3* v1, const vec3* v2, vec3* dest);
/* Add scalar to v1 and returns it*/
vec3* vec3_adds(vec3* v1, float scalar);
/* Add scalar to v1 and stores the result in dest*/
vec3* vec3_adds_c(const vec3* v1, float scalar, vec3* dest);
/* Substract v2 to v1 and returns it*/
vec3* vec3_sub(vec3* v1, const vec3* v2);
/* Substract v2 to v1 and stores the result in dest*/
vec3* vec3_sub_c(const vec3* v1, const vec3* v2, vec3* dest);
/* Substract scalar to v1 and returns it*/
vec3* vec3_subs(vec3* v1, float scalar);
/* Substract scalar to v1 and stores the result in dest*/
vec3* vec3_subs_c(const vec3* v1, float scalar, vec3* dest);
/* Performs v1* v2 and returns it*/
vec3* vec3_mul(vec3* v1, const vec3* v2);
/* Performs v1* v2 and stores the result in dest*/
vec3* vec3_mul_c(const vec3* v1, const vec3* v2, vec3* dest);
/* Performs v1* scalar and returns it*/
vec3* vec3_muls(vec3* v1, float scalar);
/* Performs v1* scalar and stores the result in dest*/
vec3* vec3_muls_c(const vec3* v1, float scalar, vec3* dest);
/* Performs v1 / v2 and returns it*/
vec3* vec3_div(vec3* v1, const vec3* v2);
/* Performs v1 / v2 and stores the result in dest*/
vec3* vec3_div_c(const vec3* v1, const vec3* v2, vec3* dest);
/* Performs v1 / scalar and returns it*/
vec3* vec3_divs(vec3* v1, float scalar);
/* Performs v1 / scalar and stores the result in dest*/
vec3* vec3_divs_c(const vec3* v1, float scalar, vec3* dest);
/* Performs the dot product between v1 and v2*/
float vec3_dot(const vec3* v1, const vec3* v2);
/* Performs the cross product between v1 and v2 and returns it*/
vec3* vec3_cross(vec3* v1, const vec3* v2);
/* Performs the cross product between v1 and v2 and stores the result in dest*/
vec3* vec3_cross_c(const vec3* v1, const vec3* v2, vec3* dest);