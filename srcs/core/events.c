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

static void	camera_rotation(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera->yaw += camera_speed;
		// camera->target.x = cosf((float)ft_to_radians(camera->yaw)) * cosf((float)ft_to_radians(camera->pitch));
		// camera->target.y = sinf((float)ft_to_radians(camera->pitch));
		// camera->target.z = sinf((float)ft_to_radians(camera->yaw)) * cosf((float)ft_to_radians(camera->pitch));
		// camera->target = vec_normalize(camera->target);
	}
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera->yaw -= camera_speed;
		// camera->target.x = cosf((float)ft_to_radians(camera->yaw)) * cosf((float)ft_to_radians(camera->pitch));
		// camera->target.y = sinf((float)ft_to_radians(camera->pitch));
		// camera->target.z = sinf((float)ft_to_radians(camera->yaw)) * cosf((float)ft_to_radians(camera->pitch));
		// camera->target = vec_normalize(camera->target);
	}
}

int			events(t_env *env)
{
	GLFWwindow	*window;
	t_camera	*camera;
	float		camera_speed;

	window = env->gl.window.ptr;
	camera = &env->camera;
	camera_speed = camera->speed * env->fps.value;
	window_events(window);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		env->texture = env->texture > TEXTURES_MAX - 1 ? 0 : env->texture + 1;
    camera_translation(window, camera, camera_speed);
	camera_rotation(window, camera, camera_speed);

	printf("target : %f %f %f\n", env->camera.target.x, env->camera.target.y, env->camera.target.z);
	printf("pos    : %f %f %f\n", env->camera.pos.x, env->camera.pos.y, env->camera.pos.z);
	if (env->camera.yaw > 180)
		env->camera.yaw = -180;
	if (env->camera.yaw < -180)
		env->camera.yaw = 180;
	printf("yaw    : %f\n", env->camera.yaw);
	return (0);
};
