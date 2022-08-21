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

// LIGHT
static void	ui_light(t_env *env)
{
	env->light.active = !env->light.active;
	glUniform1i(env->gl.uniform.light[LIGHT_ACTIVE], env->light.active);
}

// MINIFY
static void	ui_minify(t_env *env)
{
	glfwIconifyWindow(env->gl.window.ptr);
}

// MODE
static void	ui_mode(t_env *env)
{
	env->animation.active = true;
	if (env->animation.progress <= 0) {
		env->animation.step = (float)fabs(env->animation.step);
		env->animation.progress = 0;
	}
	if (env->animation.progress > 1) {
	env->animation.step = -(float)fabs(env->animation.step);
		env->animation.progress = 1;
	}
}

void		events(t_env *env)
{

	// UI ==========================================

	env->events[ACTION_UI_QUIT] = ui_quit;
	env->events[ACTION_UI_FULLSCREEN] = ui_fullscreen;
	env->events[ACTION_UI_LIGHT] = ui_light;
	env->events[ACTION_UI_MINIFY] = ui_minify;
	env->events[ACTION_UI_MODE] = ui_mode;

	events_camera(env);
	events_model(env);
};
