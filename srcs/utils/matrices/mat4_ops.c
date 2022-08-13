#include "main.h"


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

t_vec3d		mat4_x_vec3d(mat4 m, t_vec3d v)
{
	t_vec3d nv;

	nv.x = v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3];
	nv.y = v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7];
	nv.z = v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11];
	nv.w = v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15];
	return (nv);
}
