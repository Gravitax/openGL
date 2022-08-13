#include "main.h"


void		mat4_identity(mat4 m)
{
	ft_memset(m, 0, sizeof(float) * 16);
	m[0] = 1.0f;
	m[5] = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}

void		mat4_inverse(mat4 m)
{
	mat4	tmp;

	tmp[0] = m[0];
	tmp[1] = m[4];
	tmp[2] = m[8];
	tmp[3] = 0;
	tmp[4] = m[1];
	tmp[5] = m[5];
	tmp[6] = m[9];
	tmp[7] = 0;
	tmp[8] = m[2];
	tmp[9] = m[6];
	tmp[10] = m[10];
	tmp[11] = 0;
	tmp[12] = -(m[12] * tmp[0] + m[13] * tmp[4] + m[14] * tmp[8]);
	tmp[13] = -(m[12] * tmp[1] + m[13] * tmp[5] + m[14] * tmp[9]);
	tmp[14] = -(m[12] * tmp[2] + m[13] * tmp[6] + m[14] * tmp[10]);
	tmp[15] = 1;
	m = tmp;
}

void		mat4_print(mat4 m)
{
	unsigned int	i;

	for (i = 0; i < 16; i += 4)
		printf("[ %4f | %4f | %4f | %4f ]\n", m[0 + i], m[1 + i], m[2 + i], m[3 + i]);
}

void		mat4_translate(mat4 m, float x, float y, float z)
{
	m[3] += x;
	m[7] += y;
	m[11] += z;
}
