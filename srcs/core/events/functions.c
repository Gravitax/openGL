#include "../../../includes/main.h"


// UI ==========================================

// QUIT
static void	ft_quit(t_env *env)
{
	glfwSetWindowShouldClose(env->gl.window.ptr, GLFW_TRUE);
}

// FULLSCREEN
static void	ft_fullscreen(t_env *env)
{
	glfwGetWindowAttrib(env->gl.window.ptr, GLFW_MAXIMIZED)
		? glfwRestoreWindow(env->gl.window.ptr) : glfwMaximizeWindow(env->gl.window.ptr);
}

// MINIFY
static void	ft_minify(t_env *env)
{
	glfwIconifyWindow(env->gl.window.ptr);
}

// MODE
static void	ft_mode(t_env *env)
{
	env->mode = env->mode + 1 > MODE_MAX - 1 ? 0 : env->mode + 1;
	glUniform1i(env->gl.uniform.mode, env->mode);
}

// CAMERA ==========================================

// TRANSLATION FRONT
static void	ft_forward(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camera->tspeed));
}

// TRANSLATION BACK
static void	ft_backward(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camera->tspeed));
}

// TRANSLATION RIGHT
static void	ft_right(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera->tspeed));
}

// TRANSLATION LEFT
static void	ft_left(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera->tspeed));
}

// TRANSLATION UP
static void	ft_up(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camera->tspeed));
}

// TRANSLATION DOWN
static void	ft_down(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camera->tspeed));
}

void		events_init(t_env *env)
{
	// UI ==========================================

	env->events[ACTION_QUIT] = ft_quit;
	env->events[ACTION_FULLSCREEN] = ft_fullscreen;
	env->events[ACTION_MINIFY] = ft_minify;
	env->events[ACTION_MODE] = ft_mode;

	// CAMERA ==========================================

	env->events[ACTION_FORWARD] = ft_forward;
	env->events[ACTION_BACKWARD] = ft_backward;
	env->events[ACTION_RIGHT] = ft_right;
	env->events[ACTION_LEFT] = ft_left;
	env->events[ACTION_UP] = ft_up;
	env->events[ACTION_DOWN] = ft_down;
};
