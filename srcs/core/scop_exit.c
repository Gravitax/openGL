#include "../../includes/main.h"


static void	free_gl(t_env *env)
{
	t_mesh	*mesh;
	int		i;

	if (env->gl.texture)
		glDeleteTextures(1, &env->gl.texture);
	if (env->gl.shader_vertex)
		glDeleteShader(env->gl.shader_vertex);
	if (env->gl.shader_program)
		glDeleteProgram(env->gl.shader_program);
	i = -1;
	while (++i < env->model.meshs.nb_cells) {
		mesh = dyacc(&env->model.meshs, i);
		if (mesh == NULL)
			continue ;
		if (mesh->ebo)
			glDeleteBuffers(1, &mesh->ebo);
		if (mesh->vbo)
			glDeleteBuffers(1, &mesh->vbo);
		if (mesh->vao)
			glDeleteVertexArrays(1, &mesh->vao);
	}
}

static void	free_glfw(t_env *env)
{
	if (env->gl.window.ptr)
		glfwDestroyWindow(env->gl.window.ptr);
	glfwTerminate();
}

static void	free_env(t_env *env)
{
	t_mesh	*mesh;
	int		i;

	i = -1;
	while (++i < env->model.meshs.nb_cells) {
		mesh = dyacc(&env->model.meshs, i);
		if (mesh == NULL)
			continue ;
		dynarray_free(&mesh->vertices);
		dynarray_free(&mesh->faces);
		ft_strdel(&mesh->name);
	}
	dynarray_free(&env->model.meshs);
	free(env->model.texture.ptr);
}

void		scop_exit()
{
	t_env	*env;

	env = st_env(NULL, false);
	if (env == NULL)
		return ;
	free_gl(env);
	free_glfw(env);
	free_env(env);
	st_env(NULL, true);
}
