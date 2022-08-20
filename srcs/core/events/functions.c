#include "../../../includes/main.h"


// UI ==========================================

// QUIT
static void	ui_quit(t_env *env)
{
	glfwSetWindowShouldClose(env->gl.window.ptr, GLFW_TRUE);
}

// FULLSCREEN
static void	ui_fullscreen(t_env *env)
{
	glfwGetWindowAttrib(env->gl.window.ptr, GLFW_MAXIMIZED)
		? glfwRestoreWindow(env->gl.window.ptr) : glfwMaximizeWindow(env->gl.window.ptr);
}

// MINIFY
static void	ui_minify(t_env *env)
{
	glfwIconifyWindow(env->gl.window.ptr);
}

// MODE
static void	ui_mode(t_env *env)
{
	env->mode = env->mode + 1 > MODE_MAX - 1 ? 0 : env->mode + 1;
	glUniform1i(env->gl.uniform.mode, env->mode);
}

// CAMERA ==========================================

// TRANSLATION FRONT
static void	cam_forward(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camera->tspeed));
}

// TRANSLATION BACK
static void	cam_backward(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camera->tspeed));
}

// TRANSLATION RIGHT
static void	cam_right(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera->tspeed));
}

// TRANSLATION LEFT
static void	cam_left(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera->tspeed));
}

// TRANSLATION UP
static void	cam_up(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camera->tspeed));
}

// TRANSLATION DOWN
static void	cam_down(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camera->tspeed));
}

// MODEL ==========================================

static void	model_forward(t_camera *camera)
{
	mat4_translate(camera->model, 0, 0, 1);
}

static void	model_backward(t_camera *camera)
{
	mat4_translate(camera->model, 0, 0, -1);
}

static void	model_right(t_camera *camera)
{
	mat4_translate(camera->model, -1, 0, 0);
}

static void	model_left(t_camera *camera)
{
	mat4_translate(camera->model, 1, 0, 0);
}

static void	model_up(t_camera *camera)
{
	mat4_translate(camera->model, 0, 1, 0);
}

static void	model_down(t_camera *camera)
{
	mat4_translate(camera->model, 0, -1, 0);
}


void		events_init(t_env *env)
{
	// UI ==========================================

	env->events[ACTION_UI_QUIT] = ui_quit;
	env->events[ACTION_UI_FULLSCREEN] = ui_fullscreen;
	env->events[ACTION_UI_MINIFY] = ui_minify;
	env->events[ACTION_UI_MODE] = ui_mode;

	// CAMERA ==========================================

	env->events[ACTION_CAM_FORWARD] = cam_forward;
	env->events[ACTION_CAM_BACKWARD] = cam_backward;
	env->events[ACTION_CAM_RIGHT] = cam_right;
	env->events[ACTION_CAM_LEFT] = cam_left;
	env->events[ACTION_CAM_UP] = cam_up;
	env->events[ACTION_CAM_DOWN] = cam_down;

	// MODEL ==========================================

	env->events[ACTION_MODEL_FORWARD] = model_forward;
	env->events[ACTION_MODEL_BACKWARD] = model_backward;
	env->events[ACTION_MODEL_RIGHT] = model_right;
	env->events[ACTION_MODEL_LEFT] = model_left;
	env->events[ACTION_MODEL_UP] = model_up;
	env->events[ACTION_MODEL_DOWN] = model_down;
};
