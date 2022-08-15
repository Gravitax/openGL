#include "../../includes/main.h"


static void	matrices(t_gltools *gl, t_camera *camera)
{
	// Rotation XYZ matrix
	mat4_identity(camera->rot_xyz);
	mat4_rotate(camera->rot_xyz, (float)ft_to_radians(camera->pitch), (float)ft_to_radians(camera->yaw), 0);
	// Rotation XYZ reverse matrix
	mat4_identity(camera->rot_rxyz);
	mat4_rotate(camera->rot_rxyz, (float)ft_to_radians(-camera->pitch), (float)ft_to_radians(-camera->yaw), 0);
	// Model matrix
	mat4_identity(camera->model);
	mat4_translate(camera->model, 0, 0, 1);
	// View matrix
	mat4_identity(camera->view);
	// Projection matrix
	mat4_projection(camera->projection, camera->fov, camera->near, camera->far, camera->ratio);
}

void		camera(t_env *env)
{
	t_camera *camera = &env->camera;

	// RATIO
	camera->ratio = (float)_HEIGHT / (float)_WIDTH;
	// camera->ratio = (float)_WIDTH / (float)_HEIGHT;
	// Far and near plane definitions
	camera->near = 0.1f;
	camera->far = 100.0f;
	// FOV
	camera->fov = 45.0f;
	// Camera's starting position and orientation
	camera->pos = (vec3){ 1.5f, 1.75f, -2.5f };
	camera->target = (vec3){ 0, 0, 1 };
	camera->up = (vec3){ 0, 1, 0 };
	// camera->up = (vec3){ 0, -1, 0 };
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
