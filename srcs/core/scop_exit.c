#include "main.h"


static void free_gl(t_env *env)
{
	int				i = -1;

	while (++i < TEXTURES_MAX)
        glDeleteTextures(1, &env->textures[i]);
    if (env->shader_vertex)
        glDeleteShader(env->shader_vertex);
    if (env->shader_fragment)
        glDeleteShader(env->shader_fragment);
    if (env->shader_program)
        glDeleteProgram(env->shader_program);
	i = -1;
	while (++i < ELEMENTS_MAX) {
		if (env->ebo[i])
			glDeleteBuffers(1, &env->ebo[i]);
		if (env->vbo[i])
			glDeleteBuffers(1, &env->vbo[i]);
		if (env->vao[i])
			glDeleteVertexArrays(1, &env->vao[i]);
	}
}

static void	free_glfw(t_env *env)
{
	if (env->window)
        glfwDestroyWindow(env->window);
    glfwTerminate();
}

static void free_env(t_env *env)
{
    int				i = -1;

	while (++i < ELEMENTS_MAX)
		dynarray_free(&env->vertices[i]);
	i = -1;
	while (++i < TEXTURES_MAX) {
		if (env->images[i].img)
			free(env->images[i].img);
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
