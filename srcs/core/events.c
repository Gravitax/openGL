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

static void		camera_move(t_camera *camera, vec3 v, float camera_speed)
{
	mat4	m;
	vec3	dir = (vec3){ 0, 0, 0 };

	camera_speed *= 0.01f;
	printf("cs: %ff, vecfmult: %f\n", camera_speed, v.x * camera_speed);
    dir = vec_add(dir, vec_fmult(camera->xaxis, v.x * camera_speed));
    dir = vec_add(dir, vec_fmult(camera->yaxis, v.y * camera_speed));
    dir = vec_add(dir, vec_fmult(camera->zaxis, v.z * camera_speed));
	dir = vec_normalize(dir);
	camera->pos = vec_add(camera->pos, dir);
	mat4_translate(camera->view, -dir.x, -dir.y, -dir.z);
}

static void		camera_translations(GLFWwindow *window, t_camera *camera, float camera_speed)
{
	// TRANSLATION FRONT / BACK
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_move(camera, (vec3){ 0, 0, 1 }, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_move(camera, (vec3){ 0, 0, -1 }, camera_speed);
	// TRANSLATION RIGHT / LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_move(camera, (vec3){ 1, 0, 0 }, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_move(camera, (vec3){ -1, 0, 0 }, camera_speed);
	// TRANSLATION UP / DOWN
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera_move(camera, (vec3){ 0, 1, 0 }, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera_move(camera, (vec3){ 0, -1, 0 }, camera_speed);
}

int				events(t_env *env)
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
