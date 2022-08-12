#include "main.h"


void		mat4_projection(mat4 m, float fov, float near, float far, float ratio)
{
	float	e;

	mat4_identity(m);
	e = 1 / (tanf(fov / 2.0f));
	m[0] = e / ratio;
	m[5] = e;
	m[10] = (near + far) / (near - far);
	m[11] = (2 * near * far) / (near - far);
	m[14] = -1;
}

static void	matrix_pointat(mat4 m, t_vec3d from, t_vec3d to, t_vec3d up)
{
	t_vec3d		forward, new_up, right, t;

	forward = vec_normalize(vec_sub(to, from));

	t = vec_fmult(forward, vec_dot(up, forward));

	new_up = vec_sub(up, t);

	right = vec_cross(new_up, forward);

	ft_memcpy(m, &right, sizeof(t_vec3d));
	m[12] = -vec_dot(right, from);
	ft_memcpy(m + 4, &new_up, sizeof(t_vec3d));
	m[13] = -vec_dot(new_up, from);
	ft_memcpy(m + 8, &forward, sizeof(t_vec3d));
	m[14] = -vec_dot(forward, from);
	ft_memcpy(m + 12, &from, sizeof(t_vec3d));
	m[15] = 1;
}

static void	mat4_lookat(mat4 m, t_vec3d from, t_vec3d to)
{
	const t_vec3d	tmp = { 0, 1, 0 };
	t_vec3d			forward, right, up;
	
	forward = vec_normalize(vec_sub(to, from));
	right = vec_cross(vec_normalize(tmp), forward);
	up = vec_cross(forward, right);

	// m[0][0] = right.x; 
    // m[0][1] = right.y; 
    // m[0][2] = right.z; 
    // m[1][0] = up.x; 
    // m[1][1] = up.y; 
    // m[1][2] = up.z; 
    // m[2][0] = forward.x; 
    // m[2][1] = forward.y; 
    // m[2][2] = forward.z; 
    // m[3][0] = from.x; 
    // m[3][1] = from.y; 
    // m[3][2] = from.z; 
	m[0] = right.x; 
    m[4] = right.y; 
    m[8] = right.z; 
    m[1] = up.x; 
    m[5] = up.y; 
    m[9] = up.z; 
    m[2] = forward.x; 
    m[6] = forward.y; 
    m[10] = forward.z; 
    m[3] = from.x; 
    m[7] = from.y; 
    m[11] = from.z; 
}

void		mat4_view(t_camera *camera)
{
	mat4	rot;
	t_vec3d	dir, up, target;
	float	pitch, yaw, roll;

	pitch = (float)ft_to_radians(camera->pitch);
	yaw = (float)ft_to_radians(camera->yaw);
	roll = (float)ft_to_radians(camera->roll);
	mat4_rotate(rot, pitch, yaw, roll);

	dir = mat4_mult_vec(rot, camera->target);
	up = mat4_mult_vec(rot, camera->up);
	target = vec_add(camera->pos, dir);
	matrix_pointat(camera->view, camera->pos, target, up);
	// mat4_lookat(camera->view, camera->pos, target);
}
