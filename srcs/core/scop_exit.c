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
	t_mtl	*mtl;
	int		i;

	free(env->model.texture.ptr);
	i = -1;
	while (++i < env->model.meshs.nb_cells) {
		mesh = dyacc(&env->model.meshs, i);
		if (mesh == NULL)
			continue ;
		dynarray_free(&mesh->vertices);
		ft_strdel(&mesh->name);
	}
	dynarray_free(&env->model.meshs);
	dynarray_free(&env->model.faces);
	dynarray_free(&env->model.vertexs);
	dynarray_free(&env->model.vertexs_txt);
	dynarray_free(&env->model.used_mtls);
	i = -1;
	while (++i < env->model.mtls.nb_cells) {
		mtl = dyacc(&env->model.mtls, i);
		if (mtl == NULL)
			continue ;
		ft_strdel(&mtl->name);
	}
	dynarray_free(&env->model.mtls);
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
