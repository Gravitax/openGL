#include "main.h"


void		mat4_projection(mat4 m, float fov, float near, float far, float aspect)
{
	float	e;

	mat4_identity(m);
	e = 1 / (tanf(fov / 2.0f));
	m[0] = e / aspect;
	m[5] = e;
	m[10] = (near + far) / (near - far);
	m[11] = (2 * near * far) / (near - far);
	m[14] = -1;
}

static void	matrix_pointat(mat4 m, t_vec3d pos, t_vec3d target, t_vec3d up)
{
	t_vec3d		new_f, new_up, new_r, t;

	new_f = vec_sub(target, pos);
	new_f = vec_normalize(new_f);
	t = vec_fmult(new_f, vec_dot(up, new_f));
	new_up = vec_sub(up, t);
	new_r = vec_cross(new_up, new_f);
	ft_memcpy(m, &new_r, sizeof(t_vec3d));
	m[12] = -vec_dot(new_r, pos);
	ft_memcpy(m + 4, &new_up, sizeof(t_vec3d));
	m[13] = -vec_dot(new_up, pos);
	ft_memcpy(m + 8, &new_f, sizeof(t_vec3d));
	m[14] = -vec_dot(new_f, pos);
	ft_memcpy(m + 12, &pos, sizeof(t_vec3d));
	m[15] = 1;
}

void		mat4_view(t_camera *camera)
{
	mat4	rot;
	t_vec3d	dir, up, target;

	mat4_rotate(rot, (float)ft_to_radians(camera->pitch), (float)ft_to_radians(camera->yaw), (float)ft_to_radians(camera->roll));
	dir = mat4_mult_vec(rot, camera->target);
	up = mat4_mult_vec(rot, camera->up);
	target = vec_add(camera->pos, dir);
	matrix_pointat(camera->view, camera->pos, target, up);
}
