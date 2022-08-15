#ifndef LIB_VEC_H
# define LIB_VEC_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct	s_vec3
{
	float		x, y, z, w;
}				vec3;

typedef union	rsqrt
{
	float		f;
	uint32_t	i;
}				u_rsqrt;

vec3		vec_fdiv(vec3 a, float n);
vec3		vec_fmult(vec3 a, float n);
vec3		vec_fadd(vec3 a, float n);
vec3		vec_fsub(vec3 a, float n);

vec3		vec_cross(vec3 a, vec3 b);

vec3		zero_vector(void);

vec3		vec_add(vec3 a, vec3 b);
vec3		vec_sub(vec3 a, vec3 b);
vec3		vec_mult(vec3 a, vec3 b);
vec3		vec_div(vec3 a, vec3 b);
vec3		vec_relu(vec3 v);

float		ft_rsqrt(float number);
vec3		vec_normalize(vec3 vec);
float		vec_dot(vec3 a, vec3 b);
float		vec3d_dist(vec3 o, vec3 v);

#endif
