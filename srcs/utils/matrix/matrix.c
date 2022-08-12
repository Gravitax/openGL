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

static void	mat4_pointat(mat4 m, t_vec3d from, t_vec3d to, t_vec3d up)
{
	t_vec3d		forward, new_up, right;

	forward = vec_normalize(vec_sub(to, from));
	new_up = vec_fmult(forward, vec_dot(up, forward));
	new_up = vec_sub(up, new_up);
	right = vec_cross(new_up, forward);

	m[0] = right.x;
	m[1] = right.y;
	m[2] = right.z;
	m[3] = -vec_dot(right, from);
	m[3] = 0;
	m[4] = new_up.x;
	m[5] = new_up.y;
	m[6] = new_up.z;
	m[7] = -vec_dot(new_up, from);
	m[7] = 0;
	m[8] = forward.x;
	m[9] = forward.y;
	m[10] = forward.z;
	m[11] = -vec_dot(forward, from);
	m[11] = 0;
	m[12] = from.x;
	m[13] = from.y;
	m[14] = from.z;
	m[15] = 1;
}

void		mat4_lookat(mat4 m, t_vec3d position, t_vec3d target, t_vec3d up)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    t_vec3d	zaxis = vec_normalize(vec_sub(position,target));
    // 3. Get positive right axis vector
    t_vec3d	xaxis = vec_normalize(vec_cross(vec_normalize(up), zaxis));
    // 4. Calculate camera up vector
    t_vec3d	yaxis = vec_cross(zaxis, xaxis);

	mat4	translation, rotation;

	mat4_identity(translation);
    translation[3] = -position.x;
    translation[7] = -position.y;
    translation[11] = -position.z;
    mat4_identity(rotation);
    rotation[0] = xaxis.x;
    rotation[1] = xaxis.y;
    rotation[2] = xaxis.z;
    rotation[4] = yaxis.x;
    rotation[5] = yaxis.y;
    rotation[6] = yaxis.z;
    rotation[8] = zaxis.x;
    rotation[9] = zaxis.y;
    rotation[10] = zaxis.z;
    
	mat4_multiply(m, translation);
	mat4_multiply(m, rotation);
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
	// mat4_pointat(camera->view, camera->pos, target, up);
	mat4_lookat(camera->view, camera->pos, target, up);
}
