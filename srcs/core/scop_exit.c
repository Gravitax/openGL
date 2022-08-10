#include "main.h"


static void free_gl(t_env *env)
{
	int				i = -1;

	while (++i < TEXTURES_MAX)
        glDeleteTextures(1, &env->gl.textures[i]);
    if (env->gl.shader_vertex)
        glDeleteShader(env->gl.shader_vertex);
    if (env->gl.shader_fragment)
        glDeleteShader(env->gl.shader_fragment);
    if (env->gl.shader_program)
        glDeleteProgram(env->gl.shader_program);
    if (env->gl.ebo)
        glDeleteBuffers(1, &env->gl.ebo);
    if (env->gl.vbo)
        glDeleteBuffers(1, &env->gl.vbo);
    if (env->gl.vao)
        glDeleteVertexArrays(1, &env->gl.vao);
}

static void	free_glfw(t_env *env)
{
	if (env->gl.window.ptr)
        glfwDestroyWindow(env->gl.window.ptr);
    glfwTerminate();
}

static void free_env(t_env *env)
{
    int				i = -1;

	dynarray_free(&env->vertices);
	while (++i < TEXTURES_MAX) {
		if (env->images[i].ptr)
			free(env->images[i].ptr);
	}
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
