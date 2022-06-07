#include "main.h"


static void free_gl(t_env *env)
{
    if (env->tex)
        glDeleteTextures(1, &env->tex);
    if (env->shader_vertex)
        glDeleteShader(env->shader_vertex);
    if (env->shader_fragment)
        glDeleteShader(env->shader_fragment);
    if (env->shader_program)
        glDeleteProgram(env->shader_program);
    if (env->ebo)
        glDeleteBuffers(1, &env->ebo);
    if (env->vbo)
        glDeleteBuffers(1, &env->vbo);
    if (env->vao)
        glDeleteVertexArrays(1, &env->vao);
}

static void	free_glfw(t_env *env)
{
	if (env->window)
        glfwDestroyWindow(env->window);
    glfwTerminate();
}

static void free_env(t_env *env)
{
    dynarray_free(&env->vertices);
    free(env->img);
}

void        scop_exit()
{
    t_env   *env;

    env = st_env(NULL, false);
    if (env == NULL)
        return ;
    free_gl(env);
	free_glfw(env);
    free_env(env);
    st_env(NULL, true);
}
