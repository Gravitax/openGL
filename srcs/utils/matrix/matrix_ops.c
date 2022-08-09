#include "main.h"


t_vec3d		multiply_matrix(float m[4][4], t_vec3d o)
{
	t_vec3d			ret;

	ret.x = o.x * m[0][0] + o.y * m[1][0] + o.z * m[2][0] + m[3][0];
	ret.y = o.x * m[0][1] + o.y * m[1][1] + o.z * m[2][1] + m[3][1];
	ret.z = o.x * m[0][2] + o.y * m[1][2] + o.z * m[2][2] + m[3][2];
	ret.w = o.x * m[0][3] + o.y * m[1][3] + o.z * m[2][3] + m[3][3];
	return (ret);
}

void		matrix_x_vector(t_vec3d vec, float mat[4][4], float ret[4][4])
{
	float	y[4] = { vec.x, vec.y, vec.z, vec.w };
	int		i = 0, j = 0;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			ret[j][i] += mat[j][i] * y[i];
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

t_vec3d		matrix_mult_vec(float m[4][4], t_vec3d i)
{
	t_vec3d v;

	v.x = i.x * m[0][0] + i.y * m[1][0] + i.z * m[2][0] + i.w * m[3][0];
	v.y = i.x * m[0][1] + i.y * m[1][1] + i.z * m[2][1] + i.w * m[3][1];
	v.z = i.x * m[0][2] + i.y * m[1][2] + i.z * m[2][2] + i.w * m[3][2];
	v.w = i.x * m[0][3] + i.y * m[1][3] + i.z * m[2][3] + i.w * m[3][3];
	return (v);
}

void		compute_view_matrix(t_env *env)
{
	// t_cam	*cam;
	// t_vec3d	up, target, dir, pos = (t_vec3d){ 0, 0, 0, 1 };
	// float	yaw_rad, pitch_rad;

	// cam = (t_cam*)&env->scene.cam;

	// dir = (t_vec3d){0, 0, 1, 0};
	// up = (t_vec3d){0, -1, 0, 0};
	// target = (t_vec3d){0, 0, 1, 0};
	// yaw_rad = (float)ft_to_radians((double)cam->yaw);
	// pitch_rad = (float)ft_to_radians((double)cam->pitch);

	// update_yrotation_matrix(cam->mats.cry_m, yaw_rad);
	// update_xrotation_matrix(cam->mats.crx_m, pitch_rad);

	// matrix_mult_matrix(cam->mats.crx_m, cam->mats.cry_m, cam->mats.cr_m);

	// dir = matrix_mult_vec(cam->mats.cr_m, target);

	// up = matrix_mult_vec(cam->mats.cr_m, (t_vec3d){0, -1, 0, 0});

	// target = vec_add(pos, dir);

	// matrix_pointat(cam->mats.c_m, cam->pos, target, up);
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
