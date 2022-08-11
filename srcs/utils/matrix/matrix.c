#include "main.h"


void		matrix_pointat(float m[4][4], t_vec3d pos, t_vec3d target, t_vec3d up)
{
	t_vec3d		new_f;
	t_vec3d		new_up;
	t_vec3d		new_r;
	t_vec3d		t;

	new_f = vec_sub(target, pos);
	new_f = vec_normalize(new_f);
	t = vec_fmult(new_f, vec_dot(up, new_f));
	new_up = vec_sub(up, t);
	new_r = vec_cross(new_up, new_f);
	ft_memcpy(m[0], &new_r, sizeof(t_vec3d));
	m[0][3] = -vec_dot(new_r, pos);
	ft_memcpy(m[1], &new_up, sizeof(t_vec3d));
	m[1][3] = -vec_dot(new_up, pos);
	ft_memcpy(m[2], &new_f, sizeof(t_vec3d));
	m[2][3] = -vec_dot(new_f, pos);
	ft_memcpy(m[3], &pos, sizeof(t_vec3d));
	m[3][3] = 1;
}

void		matrix_view(t_camera *camera)
{
	t_vec3d		up, target, dir;
	float		yaw, pitch;

	// matrix_identity(camera->rot_x);
	// matrix_identity(camera->rot_y);
	// matrix_identity(camera->rot);

	matrix_xrotation(camera->rot_x, (float)ft_to_radians(camera->pitch));
	matrix_yrotation(camera->rot_y, (float)ft_to_radians(camera->yaw));
	matrix_mult_matrix(camera->rot_x, camera->rot_y, camera->rot);

	dir = matrix_mult_vec(camera->rot, camera->target);
	up = matrix_mult_vec(camera->rot, camera->up);
	target = vec_add(camera->pos, dir);

	matrix_pointat(camera->view, camera->pos, target, up);
}
