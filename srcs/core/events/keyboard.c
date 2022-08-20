#include "../../../includes/main.h"


static void	events_release(t_env *env, char action)
{
	int	key;

	key = 0;
	switch (action)
	{
		case (ACTION_QUIT):
			key = GLFW_KEY_ESCAPE;
		case (ACTION_FULLSCREEN):
			key = GLFW_KEY_M;
			break;
		case (ACTION_MINIFY):
			key = GLFW_KEY_I;
			break;
		case (ACTION_MODE):
			key = GLFW_KEY_T;
			break ;
	}
	if (key > 0 && glfwGetKey(env->gl.window.ptr, key) == GLFW_RELEASE) {
		(*env->events[action])(env);
		env->actions[action] = false;
	}
}

static void	events_consume(t_env *env)
{
	int	action;

	action = -1;
	while (++action < ACTION_MAX) {
		switch (action)
		{
			case (ACTION_QUIT): case (ACTION_FULLSCREEN): case (ACTION_MINIFY): case (ACTION_MODE):
				if (env->actions[action] == true)
					events_release(env, action);
				break;
			default:
				if (env->actions[action] == true) {
					(*env->events[action])(&env->camera);
					env->actions[action] = false;
				}
				break;
		}
	}
}

static void	events_detect_press(GLFWwindow *window, bool *actions)
{
	// UI ==========================================

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

	// CAMERA ==========================================

	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		actions[ACTION_FORWARD] = true;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		actions[ACTION_BACKWARD] = true;
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		actions[ACTION_UP] = true;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		actions[ACTION_DOWN] = true;
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		actions[ACTION_RIGHT] = true;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		actions[ACTION_LEFT] = true;
}

void		events_keyboard(t_env *env)
{
	env->camera.tspeed = env->camera.speed * env->fps.value * 0.01f;
	events_detect_press(env->gl.window.ptr, env->actions);
	events_consume(env);
};
