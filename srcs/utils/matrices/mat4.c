#include "../../../includes/main.h"


void		mat4_projection(mat4 m, float fov, float near, float far, float ratio)
{
	float	e;

	mat4_identity(m);
	fov = (float)ft_to_radians(fov);
	e = 1 / (tanf(fov * 0.5f));

	// HEIGHT RATIO
	m[0] = ratio * e;
	m[5] = e;
	m[10] = far / (near - far);
	m[11] = (-far * near) / (near - far);
	m[14] = 1;
	// m[15] = 0;

	// m[0] = ratio * e;
	// m[5] = e;
	// m[10] = far / (near - far);
	// m[11] = 1;
	// m[14] = (-far * near) / (near - far);
	// m[15] = 0;

	// WIDTH RATIO
	// m[0] = e / ratio;
	// m[5] = e;
	// m[10] = (near + far) / (near - far);
	// m[11] = (2 * near * far) / (near - far);
	// m[14] = -1;
}

void		mat4_lookat(mat4 m, vec3 from, vec3 to, vec3 world_up)
{
	vec3	forward, up, right, tmp;

	forward = vec_normalize(vec_sub(from, to));
    right = vec_cross(vec_normalize(world_up), forward);
    up = vec_cross(forward, right);

	// forward = vec_normalize(vec_sub(to, from));
	// tmp = vec_fmult(forward, vec_dot(up, forward));
	// up = vec_sub(world_up, tmp);
	// right = vec_cross(up, forward);

	m[0] = -right.x;
	m[1] = -right.y;
	m[2] = -right.z;
	m[3] = 0;
	m[4] = up.x;
	m[5] = up.y;
	m[6] = up.z;
	m[7] = 0;
	m[8] = forward.x;
	m[9] = forward.y;
	m[10] = forward.z;
	m[11] = 0;
	m[12] = -from.x;
	m[13] = -from.y;
	m[14] = -from.z;

	// m[0] = right.x;
	// m[4] = right.y;
	// m[8] = right.z;
	// m[12] = -vec_dot(right, from);
	// m[12] = 0;
	// m[1] = up.x;
	// m[5] = up.y;
	// m[9] = up.z;
	// m[13] = -vec_dot(up, from);
	// m[13] = 0;
	// m[2] = forward.x;
	// m[6] = forward.y;
	// m[10] = forward.z;
	// m[14] = -vec_dot(forward, from);
	// m[14] = 0;
	// m[3] = from.x;
	// m[7] = from.y;
	// m[11] = from.z;

	m[15] = 1;
}