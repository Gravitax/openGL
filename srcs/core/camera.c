#include "main.h"


static void	init_matrices(t_camera *camera)
{
	/* set the model to face positive Z and stand back */
	mat4_rotate(camera->model, 0.0f, (float)M_PI, 0.0f);
	mat4_translate(camera->model, 0, 0, -5);
	/* set the view with camera orientations and rotations */
	mat4_view(camera);
	/* set the projection with camera data */
	mat4_projection(camera->projection, (float)M_PI * camera->fov / 360.0, camera->near, camera->far, camera->aspect_ratio);
}

void		init_camera(t_env *env)
{
	t_camera *camera = &env->camera;

	// RATIO
	// camera->aspect_ratio = (float)_HEIGHT / (float)_WIDTH;
	camera->aspect_ratio = (float)_WIDTH / (float)_HEIGHT;
	// Far and near plane definitions
	camera->near = 0.1f;
	camera->far = 1000.0f;
	// FOV
	camera->fov = 90.0f;
	// Camera's starting position and orientation
	camera->pos = (t_vec3d){ 0, 0, 0, 0 };
	camera->target = (t_vec3d){ 0, 0, 1, 0 };
	camera->up = (t_vec3d){ 0, 1, 0, 0 };
	// Camera rotations
	camera->pitch = 0;
	camera->roll = 0;
	camera->yaw = 0;
	init_matrices(camera);
}
