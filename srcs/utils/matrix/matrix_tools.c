#include "main.h"


void		inverse_matrix(float m[4][4], float r[4][4])
{
	r[0][0] = m[0][0];
	r[0][1] = m[1][0];
	r[0][2] = m[2][0];
	r[0][3] = 0.0f;
	r[1][0] = m[0][1];
	r[1][1] = m[1][1];
	r[1][2] = m[2][1];
	r[1][3] = 0.0f;
	r[2][0] = m[0][2];
	r[2][1] = m[1][2];
	r[2][2] = m[2][2];
	r[2][3] = 0.0f;
	r[3][0] = -(m[3][0] * r[0][0] + m[3][1] * r[1][0] + m[3][2] * r[2][0]);
	r[3][1] = -(m[3][0] * r[0][1] + m[3][1] * r[1][1] + m[3][2] * r[2][1]);
	r[3][2] = -(m[3][0] * r[0][2] + m[3][1] * r[1][2] + m[3][2] * r[2][2]);
	r[3][3] = 1.0f;
}

void		translation_matrix(float m[4][4], t_vec3d v)
{
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}

void		matrix_flattener(float m[4][4], float flat[16])
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			flat[y * 4 + x] = m[y][x];
}

void		identity_matrix(float m[4][4])
{
	for (int i = 0; i < 4; i++) {
		ft_memset(&m[i], 0, sizeof(float) * 4);
		m[i][i] = 1;
	}
}
