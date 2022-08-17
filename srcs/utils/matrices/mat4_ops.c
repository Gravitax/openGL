#include "../../../includes/main.h"


void		mat4_multiply(mat4 a, mat4 b)
{
	unsigned int	i, j;
	mat4	res;

	for (j = 0; j < 4; j++)
		for (i = 0; i < 4; i++)
		{
			res[j * 4 + i] = a[j * 4 + 0] * b[0 * 4 + i]
				+ a[j * 4 + 1] * b[1 * 4 + i]
				+ a[j * 4 + 2] * b[2 * 4 + i]
				+ a[j * 4 + 3] * b[3 * 4 + i];
		}
	ft_memcpy(a, res, sizeof(mat4));
}

vec3		mat4_x_vec3(mat4 m, vec3 v)
{
	vec3	out;
	float	w;

	out.x = v.x * m[0] + v.y * m[1] + v.z * m[2] + m[3]; 
	out.y = v.x * m[4] + v.y * m[5] + v.z * m[6] + m[7]; 
	out.z = v.x * m[8] + v.y * m[9] + v.z * m[10] + m[11]; 
	out.w = v.x * m[12] + v.y * m[13] + v.z * m[14] + m[15]; 
	// normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
	if (out.w != 1) { 
		out.x /= out.w; 
		out.y /= out.w; 
		out.z /= out.w; 
	} 
	return (out);
}
