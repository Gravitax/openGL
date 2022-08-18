#include "../../includes/main.h"


static void update_matrices(t_camera *camera)
{
	mat4	mx, my;

	mat4_xrotation(mx, (float)ft_to_radians(-camera->yaw));
	camera->yaxis = mat4_x_vec3(mx, (vec3){ 0, 1, 0 });
	mat4_yrotation(my, (float)ft_to_radians(-camera->pitch));
	camera->xaxis = mat4_x_vec3(my, (vec3){ 1, 0, 0 });
	mat4_multiply(mx, my);
	camera->zaxis = mat4_x_vec3(mx, (vec3){ 0, 0, 1 });
}

static void	wrap_angles(t_camera *camera)
{
	camera->pitch = camera->pitch > 360 ? 0 : camera->pitch;
	camera->pitch = camera->pitch < 0 ? 360 : camera->pitch;
	camera->yaw = camera->yaw > 360 ? 0 : camera->yaw;
	camera->yaw = camera->yaw < 0 ? 360 : camera->yaw;
}

static void	update_angles(t_camera *camera, float sensitivity, float xoffset, float yoffset)
{
	float	camera_speed;

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
	update_matrices(&env->camera);
}

static void	window_events(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glfwGetWindowAttrib(window, GLFW_MAXIMIZED) ? glfwRestoreWindow(window) : glfwMaximizeWindow(window);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		glfwIconifyWindow(window);
}

static void	camera_move(t_camera *camera, vec3 v, float camera_speed)
{
	mat4	m;
	vec3	dir = (vec3){ 0, 0, 0 };

	camera_speed *= 0.01f;
    dir = vec_add(dir, vec_fmult(camera->yaxis, v.y * camera_speed));
    dir = vec_add(dir, vec_fmult(camera->xaxis, v.x * camera_speed));
    dir = vec_add(dir, vec_fmult(camera->zaxis, v.z * camera_speed));
	camera->pos = vec_add(camera->pos, dir);
}

static void	camera_translations(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_move(camera, camera->zaxis, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_move(camera, vec_fmult(camera->zaxis, -1), camera_speed);
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_move(camera, camera->xaxis, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_move(camera, vec_fmult(camera->xaxis, -1), camera_speed);
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera_move(camera, camera->yaxis, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera_move(camera, vec_fmult(camera->yaxis, -1), camera_speed);
}

int			events(t_env *env)
{
	GLFWwindow	*window;
	t_camera	*camera;

	window = env->gl.window.ptr;
	window_events(window);
	camera = &env->camera;
    camera_translations(window, camera, camera->speed * env->fps.value);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		env->texture = env->texture > TEXTURES_MAX - 1 ? 0 : env->texture + 1;
	return (0);
};
