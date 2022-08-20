#include "../../../includes/main.h"


static void	events_release(t_env *env, char action)
{
	int	key;

	key = 0;
	switch (action)
	{
		case (ACTION_UI_QUIT):
			key = GLFW_KEY_ESCAPE;
		case (ACTION_UI_FULLSCREEN):
			key = GLFW_KEY_M;
			break;
		case (ACTION_UI_MINIFY):
			key = GLFW_KEY_I;
			break;
		case (ACTION_UI_MODE):
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
	int	i;

	i = -1;
	while (++i < ACTION_MAX) {
		switch (i)
		{
			case (ACTION_UI_QUIT): case (ACTION_UI_FULLSCREEN): case (ACTION_UI_MINIFY): case (ACTION_UI_MODE):
				if (env->actions[i] == true)
					events_release(env, i);
				break;
			default:
				if (env->actions[i] == true) {
					(*env->events[i])(&env->camera);
					env->actions[i] = false;
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
		actions[ACTION_UI_QUIT] = true;
	// FULLSCREEN
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		actions[ACTION_UI_FULLSCREEN] = true;
	// MINIFY
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		actions[ACTION_UI_MINIFY] = true;
	// MODE
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		actions[ACTION_UI_MODE] = true;

	// CAMERA ==========================================

	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		actions[ACTION_CAM_FORWARD] = true;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		actions[ACTION_CAM_BACKWARD] = true;
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		actions[ACTION_CAM_RIGHT] = true;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		actions[ACTION_CAM_LEFT] = true;
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		actions[ACTION_CAM_UP] = true;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		actions[ACTION_CAM_DOWN] = true;

	// MODEL ==========================================

	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		actions[ACTION_MODEL_FORWARD] = true;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		actions[ACTION_MODEL_BACKWARD] = true;
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		actions[ACTION_MODEL_RIGHT] = true;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		actions[ACTION_MODEL_LEFT] = true;
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		actions[ACTION_MODEL_UP] = true;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		actions[ACTION_MODEL_DOWN] = true;
}

void		events_keyboard(t_env *env)
{
	env->camera.tspeed = env->camera.speed * env->fps.value * 0.01f;
	events_detect_press(env->gl.window.ptr, env->actions);
	events_consume(env);
};
