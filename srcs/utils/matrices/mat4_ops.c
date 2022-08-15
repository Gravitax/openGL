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
	vec3	nv;

	nv.x = v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3];
	nv.y = v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7];
	nv.z = v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11];
	nv.w = v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15];

	nv.x = v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12];
	nv.y = v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13];
	nv.z = v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14];
	nv.w = v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15];
	return (nv);
}
