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

void		matrix_mult_matrix(float m1[4][4], float m2[4][4], float ret[4][4])
{
	unsigned int	c;
	unsigned int	r;
	float			tmp;

	c = 0;
	while (c < 4)
	{
		r = 0;
		while (r < 4)
		{
			tmp = m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c];
			tmp += m1[r][2] * m2[2][c] + m1[r][3] * m2[3][c];
			ret[r][c] = tmp;
			r++;
		}
		c++;
	}
}
