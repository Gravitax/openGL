#include "../../includes/main.h"


static void	matrices(t_gltools *gl, t_camera *camera)
{
	// Model matrix
	mat4_identity(camera->model);
	// View matrix
	mat4_identity(camera->view);
	// Projection matrix
	mat4_projection(camera->projection, camera->fov, camera->near, camera->far, camera->ratio);
}

void		camera(t_env *env)
{
	t_camera *camera = &env->camera;

	// RATIO
	// camera->ratio = (float)_HEIGHT / (float)_WIDTH;
	camera->ratio = (float)_WIDTH / (float)_HEIGHT;
	// Far and near plane definitions
	camera->near = 0.1f;
	camera->far = 100.0f;
	// FOV
	camera->fov = 45.0f;
	// Camera starting position and orientation
	camera->pos = (vec3){ 1, 1, -10 };
	camera->xaxis = (vec3){ 1, 0, 0 };
	camera->yaxis = (vec3){ 0, 1, 0 };
	camera->zaxis = (vec3) { 0, 0, 1 };
	// Camera movements speed
	camera->speed = 1.0f;
	camera->sensitivity = 1.0f;
	// Camera rotations
	camera->pitch = 0;
	camera->yaw = 0;
	matrices(&env->gl, camera);
	// Mouse
	camera->first_mouse = true;
	glfwSetInputMode(env->gl.window.ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
