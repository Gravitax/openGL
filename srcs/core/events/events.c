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

void		events(t_env *env)
{

	// UI ==========================================

	env->events[ACTION_UI_QUIT] = ui_quit;
	env->events[ACTION_UI_FULLSCREEN] = ui_fullscreen;
	env->events[ACTION_UI_MINIFY] = ui_minify;
	env->events[ACTION_UI_MODE] = ui_mode;

	events_camera(env);
	events_model(env);
};
