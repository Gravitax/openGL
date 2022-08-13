#include "main.h"


static void	init_matrices(t_camera *camera)
{
	/* set the model to face positive Z and stand back */
	mat4_rotate(camera->model, 0, (float)M_PI, 0);
	mat4_translate(camera->model, 0, 0, -1);
	/* set the view with camera orientations and rotations */
	mat4_view(camera);
	/* set the projection with camera data */
	mat4_projection(camera->projection, (float)ft_to_radians(camera->fov), camera->near, camera->far, camera->ratio);
}

void		init_camera(t_env *env)
{
	t_camera *camera = &env->camera;

	// RATIO
	camera->ratio = (float)_WIDTH / (float)_HEIGHT;
	// Far and near plane definitions
	camera->near = 0.1f;
	camera->far = 1000.0f;
	// FOV
	camera->fov = 90.0f;
	// Camera's starting position and orientation
	camera->pos = (t_vec3d){ 0, 0, 0, 1 };
	camera->target = (t_vec3d){ 0, 0, 1, 1 };
	camera->up = (t_vec3d){ 0, 1, 0, 1 };
	// Camera rotations
	camera->pitch = 0;
	camera->roll = 0;
	camera->yaw = 0;
	init_matrices(camera);
}
