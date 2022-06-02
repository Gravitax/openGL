#include "main.h"


static void gl_set_fps(t_env *env)
{
    double  ms_per_frame;

    ms_per_frame = 1000.f / env->frames;
    env->fps = 1 / ms_per_frame * 1000.f;
}

void        gl_fps(t_env *env, bool print)
{
    double  currentTime;

    currentTime = glfwGetTime();
    ++env->frames;
    if (currentTime - env->time >= 1.f) // si il y a une diff de plus d'1 seconde
    {
        gl_set_fps(env);
        env->frames = 0;
        ++env->time;
        print ? printf("fps: %d\n", env->fps) : 0;
    }
}
