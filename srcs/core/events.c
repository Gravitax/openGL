#include "main.h"


static void	window_events(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glfwGetWindowAttrib(window, GLFW_MAXIMIZED) ? glfwRestoreWindow(window) : glfwMaximizeWindow(window);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		glfwIconifyWindow(window);
}

static void	camera_translation(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	camera_speed *= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->target, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->target, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->up, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->up, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->target, camera->up), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->target, camera->up), camera_speed));
}

static void	camera_update(t_camera *camera)
{
	camera->pitch = camera->pitch > 90 ? 90 : camera->pitch;
	camera->pitch = camera->pitch < -90 ? -90 : camera->pitch;
	camera->yaw = camera->yaw > 180 ? -180 : camera->yaw;
	camera->yaw = camera->yaw < -180 ? 180 : camera->yaw;

	mat4_identity(camera->rot_xyz);
	mat4_rotate(camera->rot_xyz, (float)ft_to_radians(camera->pitch), (float)ft_to_radians(camera->yaw), (float)ft_to_radians(camera->roll));
	camera->pos = mat4_x_vec3d(camera->rot_xyz, camera->pos);
}

static void	camera_rotation(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	camera_speed *= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera->yaw += camera_speed;
		camera_update(camera);
	}
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera->yaw -= camera_speed;
		camera_update(camera);
	}
	printf("pos    : %f %f %f\n", camera->pos.x, camera->pos.y, camera->pos.z);
	// printf("pitch  : %f\n", camera->pitch);
	printf("yaw    : %f\n", camera->yaw);
	// printf("roll   : %f\n", camera->roll);
}

int			events(t_env *env)
{
	GLFWwindow	*window;
	t_camera	*camera;
	float		camera_speed;

	window = env->gl.window.ptr;
	window_events(window);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		env->texture = env->texture > TEXTURES_MAX - 1 ? 0 : env->texture + 1;

	camera = &env->camera;
	camera_speed = camera->speed * env->fps.value;
    camera_translation(window, camera, camera_speed);
	camera_rotation(window, camera, camera_speed);
	return (0);
};
