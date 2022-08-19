#include "../../includes/main.h"


static void	init_camera(t_camera *camera)
{
	camera->ground_fixed = false;
	// RATIO
	camera->ratio = (float)_WIDTH / (float)_HEIGHT;
	// Far and near plane definitions
	camera->near = 0.1f;
	camera->far = 100.0f;
	// FOV
	camera->fov = 45.0f;
	// Camera starting position and orientation
	camera->pos = (vec3){ 0, 0, -50 };
	camera->yaxis = (vec3){ 0, 1, 0 };
	camera->zaxis = (vec3) { 0, 0, 1 };
	// Camera movements speed
	camera->speed = 1.0f;
	// Camera rotations angles
	camera->pitch = 0;
	camera->yaw = 0;
}

static void	init_matrices(t_gltools *gl, t_camera *camera)
{
	// Model matrix
	mat4_identity(camera->model);
	// View matrix
	mat4_identity(camera->view);
	// Projection matrix
	mat4_projection(camera->projection, camera->fov, camera->near, camera->far, camera->ratio);
}

static void	init_mouse(GLFWwindow *window, t_mouse *mouse)
{
	mouse->mounted = false;
	mouse->sensitivity = 1.0f;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void		camera(t_env *env)
{
	init_camera(&env->camera);
	init_matrices(&env->gl, &env->camera);
	init_mouse(env->gl.window.ptr, &env->mouse);
}
