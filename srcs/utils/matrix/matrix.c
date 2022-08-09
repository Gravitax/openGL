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

void		compute_projection_matrix(t_env *env)
{
	t_vec3d		up, target, dir, pos;
	float		yaw_rad, pitch_rad;
	t_camera	camera;

	dir = (t_vec3d){0, 0, 1, 0};
	target = (t_vec3d){0, 0, 1, 0};
	pos = (t_vec3d){ 0, 0, 0, 1 };

	camera = env->camera;
	yaw_rad = (float)ft_to_radians(camera.yaw);
	pitch_rad = (float)ft_to_radians(camera.pitch);

	identity_matrix(camera.rot_x);
	identity_matrix(camera.rot_y);
	identity_matrix(camera.rot);

	update_xrotation_matrix(camera.rot_x, pitch_rad);
	update_yrotation_matrix(camera.rot_y, yaw_rad);
	matrix_mult_matrix(camera.rot_x, camera.rot_y, camera.rot);

	dir = matrix_mult_vec(camera.rot, target);
	up = matrix_mult_vec(camera.rot, (t_vec3d){0, -1, 0, 0});
	target = vec_add(pos, dir);

	matrix_pointat(camera.cam, pos, target, up);
}

void		compute_rotation_matrix(float rot_xyz[4][4])
{
	float	rot_xy[4][4], rot_x[4][4], rot_y[4][4], rot_z[4][4];

	identity_matrix(rot_x);
	identity_matrix(rot_y);
	identity_matrix(rot_z);
	identity_matrix(rot_xy);
	identity_matrix(rot_xyz);

	update_xrotation_matrix(rot_x, 0);
	update_yrotation_matrix(rot_y, 0);
	update_zrotation_matrix(rot_z, 0);
	matrix_mult_matrix(rot_x, rot_y, rot_xy);
	matrix_mult_matrix(rot_xy, rot_z, rot_xyz);
}
