#include "../../includes/main.h"


static void	events_release(t_env *env, char action, int key)
{
	if (glfwGetKey(env->gl.window.ptr, key) == GLFW_RELEASE) {
		switch (action)
		{
			case (ACTION_QUIT):
				glfwSetWindowShouldClose(env->gl.window.ptr, GLFW_TRUE);
			case (ACTION_FULLSCREEN):
				glfwGetWindowAttrib(env->gl.window.ptr, GLFW_MAXIMIZED)
					? glfwRestoreWindow(env->gl.window.ptr) : glfwMaximizeWindow(env->gl.window.ptr);
				break;
			case (ACTION_MINIFY):
				glfwIconifyWindow(env->gl.window.ptr);
				break;
			case (ACTION_MODE):
				env->mode = env->mode + 1 > MODE_MAX - 1 ? 0 : env->mode + 1;
				glUniform1i(env->gl.uniform.mode, env->mode);
				break ;
		}
		env->actions[action] = false;
	}
}

static void	events_on_release(t_env *env, char action)
{
	int	event;

	event = 0;
	switch (action)
	{
		case (ACTION_QUIT):
			event = GLFW_KEY_ESCAPE;
		case (ACTION_FULLSCREEN):
			event = GLFW_KEY_M;
			break;
		case (ACTION_MINIFY):
			event = GLFW_KEY_I;
			break;
		case (ACTION_MODE):
			event = GLFW_KEY_T;
			break ;
	}
	events_release(env, action, event);
}

static void	events_on_press(t_env *env, char action)
{
	t_camera	*camera;
	float		camspeed;

	camera = &env->camera;
	camspeed = camera->speed * env->fps.value * 0.01f;
	switch (action)
	{
		case (ACTION_FORWARD):
			camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camspeed));
			break;
		case (ACTION_BACKWARD):
			camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camspeed));
			break;
		case (ACTION_RIGHT):
			camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camspeed));
			break;
		case (ACTION_LEFT):
			camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camspeed));
			break;
		case (ACTION_UP):
			camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camspeed));
			break;
		case (ACTION_DOWN):
			camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camspeed));
			break;
	}
	env->actions[action] = false;
}

static void	events_consume(t_env *env)
{
	int	i;

	i = -1;
	while (++i < ACTIONS_MAX) {
		switch (i)
		{
			case (ACTION_QUIT): case (ACTION_FULLSCREEN): case (ACTION_MINIFY): case (ACTION_MODE):
				if (env->actions[i] == true)
					events_on_release(env, i);
				break;
			// default:
			// 	if (env->actions[i] == true)
			// 		events_on_press(env, i);
			// 	break;
		}
	}
}

static void	events_camera(GLFWwindow *window, t_camera *camera, bool *actions, float camspeed)
{
	// // TRANSLATION FRONT / BACK
	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	// 	actions[ACTION_FORWARD] = true;
	// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	// 	actions[ACTION_BACKWARD] = true;
	// // TRANSLATION UP / DOWN
	// if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	// 	actions[ACTION_UP] = true;
	// if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	// 	actions[ACTION_DOWN] = true;
	// // TRANSLATION RIGHT / LEFT
	// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	// 	actions[ACTION_RIGHT] = true;
	// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	// 	actions[ACTION_LEFT] = true;

	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camspeed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camspeed));
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camspeed));
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camspeed));
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camspeed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camspeed));
}

static void	events_ui(GLFWwindow *window, bool *actions)
{
	// QUIT
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		actions[ACTION_QUIT] = true;
	// FULLSCREEN
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		actions[ACTION_FULLSCREEN] = true;
	// MINIFY
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		actions[ACTION_MINIFY] = true;
	// MODE
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		actions[ACTION_MODE] = true;
}

int			events(t_env *env)
{
	events_ui(env->gl.window.ptr, env->actions);
	events_camera(env->gl.window.ptr, &env->camera, env->actions, env->camera.speed * env->fps.value * 0.01f);
	events_consume(env);
	return (0);
};
