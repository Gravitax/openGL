#include "../../includes/main.h"


static void		window_events(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glfwGetWindowAttrib(window, GLFW_MAXIMIZED) ? glfwRestoreWindow(window) : glfwMaximizeWindow(window);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		glfwIconifyWindow(window);
}

static void		camera_translations(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	vec3	target;

	camera_speed *= 0.001f;

	// target.x = cosf(-camera->yaw) * cosf(-camera->pitch);
    // target.y = sinf(-camera->pitch);
    // target.z = sinf(-camera->yaw) * cosf(-camera->pitch);

	target = mat4_x_vec3(camera->rot_rxyz, camera->target);

	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(target, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(target, camera_speed));
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->up, target), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->up, target), camera_speed));
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, vec_fmult(camera->up, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, vec_fmult(camera->up, camera_speed));
}

int				events(t_env *env)
{
	GLFWwindow	*window;
	t_camera	*camera;
	float		camera_speed;

	window = env->gl.window.ptr;
	window_events(window);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		env->texture = env->texture > TEXTURES_MAX - 1 ? 0 : env->texture + 1;

	camera = &env->camera;
	camera_speed = camera->speed * env->fps.value;
    camera_translations(window, camera, camera_speed);
	return (0);
};
