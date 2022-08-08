#include "main.h"


void        glfw_fps(t_env *env, bool print)
{
    double	current_seconds = glfwGetTime();
	double	elapsed_seconds = current_seconds - env->time;

	if (elapsed_seconds > 1) {
		env->time = current_seconds;
		double	fps = (double)env->frames / elapsed_seconds;

		env->fps = fps;
		print ? printf("fps: %d\n", env->fps) : 0;
		env->frames = 0;
	}
	++env->frames;
}
