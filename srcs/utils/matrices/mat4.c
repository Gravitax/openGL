#include "main.h"


void		mat4_projection(mat4 m, float fov, float near, float far, float ratio)
{
	float	e;

	mat4_identity(m);
	fov = (float)ft_to_radians(fov);
	e = 1 / (tanf(fov * 0.5f));
	
	// WIDTH RATIO
	// m[0] = e / ratio;
	// m[5] = e;
	// m[10] = (near + far) / (near - far);
	// m[11] = (2 * near * far) / (near - far);
	// m[14] = -1;

	// HEIGHT RATIO
	m[0] = ratio * e;
	m[5] = e;
	m[10] = far / (near - far);
	m[11] = (-far * near) / (near - far);
	m[14] = 1;
}

static void	mat4_pointat(mat4 m, t_vec3d from, t_vec3d to, t_vec3d world_up)
{
	t_vec3d		forward, up, right;

	// forward = vec_sub(to, from);
	// up = vec_fmult(forward, vec_dot(world_up, forward));
	// up = vec_sub(world_up, up);
	// right = vec_cross(up, forward);

	forward = vec_sub(to, from);
    right = vec_cross(world_up, forward);
    up = vec_cross(forward, right);

	m[0] = right.x;
	m[1] = right.y;
	m[2] = right.z;
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
	m[15] = 1;
}

void		mat4_view(t_camera *camera)
{
	mat4	rot;
	t_vec3d	dir, up, target;

	mat4_rotate(rot,
		(float)ft_to_radians(camera->pitch), (float)ft_to_radians(camera->yaw), (float)ft_to_radians(camera->roll),
		(t_vec3d){ camera->pos.x, camera->pos.y, camera->pos.z });

	dir = mat4_x_vec3d(rot, camera->target);
	target = vec_add(camera->pos, camera->target);
	up = mat4_x_vec3d(rot, camera->up);
	
	mat4_pointat(camera->view, camera->pos, target, up);
	
	// mat4_pointat(camera->view, camera->pos, vec_add(camera->pos, camera->target), camera->up);
}
