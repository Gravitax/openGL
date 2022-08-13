#include "main.h"


static void	init_matrices(t_gltools *gl, t_camera *camera)
{
	/* set the model and stand back */
	mat4_identity(camera->model);
	mat4_translate(camera->model, 0, 0, -1);
	/* set the view with camera orientations and rotations */
	mat4_view(camera);
	/* set the projection with camera data */
	mat4_projection(camera->projection, (float)ft_to_radians(camera->fov), camera->near, camera->far, camera->ratio);
    glUniformMatrix4fv(gl->uniform.projection, 1, GL_FALSE, camera->projection);
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
	camera->fov = 45.0f;
	// Camera's starting position and orientation
	camera->pos = (t_vec3d){ 0, 0, -2, 1 };
	camera->target = (t_vec3d){ 0, 0, 1, 1 };
	camera->up = (t_vec3d){ 0, 1, 0, 1 };
	camera->speed = 0.1f;
	// Camera rotations
	camera->pitch = 0;
	camera->roll = 0;
	camera->yaw = 0;
	init_matrices(&env->gl, camera);
}
