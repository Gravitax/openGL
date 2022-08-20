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
		case (ACTION_UI_RSHIFT):
			key = GLFW_KEY_RIGHT_SHIFT;
			break ;
		case (ACTION_UI_LSHIFT):
			key = GLFW_KEY_LEFT_SHIFT;
			break ;
	}
	if (glfwGetKey(env->gl.window.ptr, key) == GLFW_RELEASE) {
		if (env->events[action])
			(*env->events[action])(env);
		env->actions[action] = false;
	}
}

static void	events_consume(t_env *env)
{
	int	i;

	i = -1;
	while (++i < ACTION_MAX) {
		if (i <= ACTION_UI_RSHIFT && env->actions[i] == true) { // RELEASE EVENTS
			events_release(env, i);
		}
		else if (i >= ACTION_CAM_FORWARD && i <= ACTION_CAM_DOWN && env->actions[i] == true) { // CAM EVENTS
			if (env->events[i])
				(*env->events[i])(&env->camera);
			env->actions[i] = false;
		}
		else if (i >= ACTION_MODEL_FORWARD && i <= ACTION_MODEL_NROTZ && env->actions[i] == true) { // MODEL EVENTS
			if (env->events[i])
				(*env->events[i])(&env->model);
			env->actions[i] = false;
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
	// RSHIFT
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		actions[ACTION_UI_RSHIFT] = true;
	// LSHIFT
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		actions[ACTION_UI_LSHIFT] = true;

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

	bool	shift = actions[ACTION_UI_RSHIFT] || actions[ACTION_UI_LSHIFT];

	// FRONT / BACK / ROT X
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		actions[shift ? ACTION_MODEL_PROTX : ACTION_MODEL_FORWARD] = true;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		actions[shift ? ACTION_MODEL_NROTX : ACTION_MODEL_BACKWARD] = true;
	// RIGHT / LEFT / ROT Y
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		actions[shift ? ACTION_MODEL_PROTY : ACTION_MODEL_RIGHT] = true;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		actions[shift ? ACTION_MODEL_NROTY : ACTION_MODEL_LEFT] = true;
	// UP / DOWN / ROT Z
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		actions[shift ? ACTION_MODEL_PROTZ : ACTION_MODEL_UP] = true;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		actions[shift ? ACTION_MODEL_NROTZ : ACTION_MODEL_DOWN] = true;
}

void		events_keyboard(t_env *env)
{
	env->camera.tspeed = env->camera.speed * env->fps.value * 0.01f;
	events_detect_press(env->gl.window.ptr, env->actions);
	events_consume(env);
};
