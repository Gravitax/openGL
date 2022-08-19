#include "../../includes/main.h"


static void update_directions(t_camera *camera)
{
	camera->zaxis.x = -sinf((float)ft_to_radians(camera->pitch)) * cosf((float)ft_to_radians(camera->yaw));
	camera->zaxis.y = sinf((float)ft_to_radians(camera->yaw));
	camera->zaxis.z = cosf((float)ft_to_radians(camera->pitch)) * cosf((float)ft_to_radians(camera->yaw));
}

static void	wrap_angles(t_camera *camera)
{
	camera->pitch = camera->pitch > 360 ? 0 : camera->pitch;
	camera->pitch = camera->pitch < 0 ? 360 : camera->pitch;
	if (camera->ground_fixed == true) {
		camera->yaw = camera->yaw > 45 ? 45 : camera->yaw;
		camera->yaw = camera->yaw < -45 ? -45 : camera->yaw;
	} else {
		camera->yaw = camera->yaw > 90 ? 90 : camera->yaw;
		camera->yaw = camera->yaw < -90 ? -90 : camera->yaw;
	}
}

static void	update_angles(t_camera *camera, float sensitivity, float xoffset, float yoffset)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	camera->pitch += xoffset;
	camera->yaw += yoffset;
	wrap_angles(camera);
}

void		events_mouse(t_env *env, float xpos, float ypos)
{
	t_mouse	*mouse;
	float	xoffset, yoffset;

	mouse = &env->mouse;
	if (mouse->mounted == false)
	{
		mouse->pos.x = xpos;
		mouse->pos.y = ypos;
		mouse->mounted = true;
	}
	xoffset = xpos - mouse->pos.x;
	yoffset = mouse->pos.y - ypos;
	mouse->pos.x = xpos;
	mouse->pos.y = ypos;
	update_angles(&env->camera, mouse->sensitivity * 0.005f, xoffset, yoffset);
	update_directions(&env->camera);
}

static void	events_window(GLFWwindow *window, char *action)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		*action = A_QUIT;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		*action = A_FULLSCREEN;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		*action = A_MINIFY;
}

static void	events_camera(t_env *env)
{
	GLFWwindow	*window;

	window = env->gl.window.ptr;
	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		env->action = A_FORWARD;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		env->action = A_BACKWARD;
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		env->action = A_UP;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		env->action = A_DOWN;
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		env->action = A_RIGHT;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		env->action = A_LEFT;
}

static void	evnets_smooth()
{

}

static void	events_toggle(t_env *env)
{
	switch (env->action)
	{
		case (A_QUIT):
			glfwSetWindowShouldClose(env->gl.window.ptr, GLFW_TRUE);
		case (A_FULLSCREEN):
			glfwGetWindowAttrib(env->gl.window.ptr, GLFW_MAXIMIZED)
				? glfwRestoreWindow(env->gl.window.ptr) : glfwMaximizeWindow(env->gl.window.ptr);
			break;
		case (A_MINIFY):
			glfwIconifyWindow(env->gl.window.ptr);
			break;
		case (A_MODE):
			env->mode = env->mode + 1 > MODE_MAX - 1 ? 0 : env->mode + 1;
			glUniform1i(env->gl.uniform.mode, env->mode);
			break ;
	}
}

static void	events_handler(t_env *env)
{
	t_camera	*camera;
	float		camera_speed;

	camera = &env->camera;
	camera_speed = camera->speed * env->fps.value * 0.01f;
	switch (env->action)
	{
		case (A_QUIT): case (A_FULLSCREEN): case (A_MINIFY): case (A_MODE):
			events_toggle(env);
			break;
		case (A_FORWARD):
			camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camera_speed));
			break;
		case (A_BACKWARD):
			camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camera_speed));
			break;
		case (A_RIGHT):
			camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera_speed));
			break;
		case (A_LEFT):
			camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera_speed));
			break;
		case (A_UP):
			camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camera_speed));
			break;
		case (A_DOWN):
			camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camera_speed));
			break;
	}
}

int			events(t_env *env)
{

	env->action = 0;
	events_window(env->gl.window.ptr, &env->action);
	events_camera(env);
	// light
	if (glfwGetKey(env->gl.window.ptr, GLFW_KEY_T) == GLFW_PRESS)
		env->action = A_MODE;
	if (env->action)
		events_handler(env);
	return (0);
};
