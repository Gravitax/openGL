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

static void	events_window(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glfwGetWindowAttrib(window, GLFW_MAXIMIZED) ? glfwRestoreWindow(window) : glfwMaximizeWindow(window);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		glfwIconifyWindow(window);
}

static void	camera_translations(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camera_speed));
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camera_speed));
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera_speed));
}

int			events(t_env *env)
{
	GLFWwindow	*window;
	t_camera	*camera;

	window = env->gl.window.ptr;
	events_window(window);
	camera = &env->camera;
	camera_translations(window, camera, camera->speed * env->fps.value * 0.01f);
	return (0);
};
