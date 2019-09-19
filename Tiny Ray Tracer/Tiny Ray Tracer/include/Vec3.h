#pragma once

typedef struct Vec3
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
} Vec3;

/* Create a vector with the specified values */
Vec3 vec3_create(float x, float y, float z);
/* Create a vector with the specified values */
Vec3 vec3_create_val(float xyz);
/* Set all components of this vector to the given values*/
Vec3* vec3_set(Vec3* vec, float x, float y, float z);
/* Returns the length of the given vector*/
float vec3_length(const Vec3* vec);
/* Returns the squared length of the given vector*/
float vec3_sqrtlen(const Vec3* vec);
/* Normalizes the given vector*/
Vec3* vec3_normalize(Vec3* vec);
/* Normalizes the given vector and stores the result in dest*/
Vec3* vec3_normalize_c(const Vec3* vec, Vec3* dest);
/* Negates the given vector*/
Vec3* vec3_negate(Vec3* vec);
/* Negates the given vector and stores the result in dest*/
Vec3* vec3_negate_c(const Vec3* vec, Vec3* dest);
/* Add v2 to v1 and returns it*/
Vec3* vec3_add(Vec3* v1, const Vec3* v2);
/* Add v2 to v1 and stores the result in dest*/
Vec3* vec3_add_c(const Vec3* v1, const Vec3* v2, Vec3* dest);
/* Add scalar to v1 and returns it*/
Vec3* vec3_adds(Vec3* v1, float scalar);
/* Add scalar to v1 and stores the result in dest*/
Vec3* vec3_adds_c(const Vec3* v1, float scalar, Vec3* dest);
/* Substract v2 to v1 and returns it*/
Vec3* vec3_sub(Vec3* v1, const Vec3* v2);
/* Substract v2 to v1 and stores the result in dest*/
Vec3* vec3_sub_c(const Vec3* v1, const Vec3* v2, Vec3* dest);
/* Substract scalar to v1 and returns it*/
Vec3* vec3_subs(Vec3* v1, float scalar);
/* Substract scalar to v1 and stores the result in dest*/
Vec3* vec3_subs_c(const Vec3* v1, float scalar, Vec3* dest);
/* Performs v1* v2 and returns it*/
Vec3* vec3_mul(Vec3* v1, const Vec3* v2);
/* Performs v1* v2 and stores the result in dest*/
Vec3* vec3_mul_c(const Vec3* v1, const Vec3* v2, Vec3* dest);
/* Performs v1* scalar and returns it*/
Vec3* vec3_muls(Vec3* v1, float scalar);
/* Performs v1* scalar and stores the result in dest*/
Vec3* vec3_muls_c(const Vec3* v1, float scalar, Vec3* dest);
/* Performs v1 / v2 and returns it*/
Vec3* vec3_div(Vec3* v1, const Vec3* v2);
/* Performs v1 / v2 and stores the result in dest*/
Vec3* vec3_div_c(const Vec3* v1, const Vec3* v2, Vec3* dest);
/* Performs v1 / scalar and returns it*/
Vec3* vec3_divs(Vec3* v1, float scalar);
/* Performs v1 / scalar and stores the result in dest*/
Vec3* vec3_divs_c(const Vec3* v1, float scalar, Vec3* dest);
/* Performs the dot product between v1 and v2*/
float vec3_dot(const Vec3* v1, const Vec3* v2);
/* Performs the cross product between v1 and v2 and returns it*/
Vec3* vec3_cross(Vec3* v1, const Vec3* v2);
/* Performs the cross product between v1 and v2 and stores the result in dest*/
Vec3* vec3_cross_c(const Vec3* v1, const Vec3* v2, Vec3* dest);
/* Makes a copy of the given vector */
Vec3 vec3_copy(const Vec3* src);
/* Makes a copy of the given vector and stores the result in dest*/
Vec3* vec3_copy_to(const Vec3* src, Vec3* dest);