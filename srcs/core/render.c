#include "../../includes/main.h"


static void	mat4_view(t_camera *camera)
{
	if (camera->ground_fixed == true)
		camera->pos.y = 0;
	mat4_lookat(camera->view, camera->pos, vec_add(camera->pos, camera->zaxis), camera->yaxis);
	mat4_inverse(camera->view);
}

// static void	mat4_mvp(t_camera *camera)
// {
// 	mat4_identity(camera->mvp);
// 	mat4_multiply(camera->mvp, camera->projection);
// 	mat4_multiply(camera->mvp, camera->view);
// 	mat4_multiply(camera->mvp, camera->model);
// }

static void	textures(GLuint *textures, int id)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_MAX) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[id]);
	}
}

static void	draw_mesh(t_env *env)
{
	t_mesh	*mesh;
	int		i;

	i = -1;
	while (++i < env->mesh.nb_cells) {
		mesh = dyacc(&env->mesh, i);
		if (mesh == NULL)
			continue ;
		textures(env->gl.textures, mesh->texture);
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.nb_cells);
		glBindVertexArray(0);
	}
}

static void	draw(t_env *env) {
	t_camera		*camera;

	camera = &env->camera;
	mat4_view(camera);

	// update camera pos in shaders
	glUniform4fv(env->gl.uniform.light[LIGHT_POSITION], 1, (GLfloat *)&env->camera.pos);

	// update matrices in shaders
	glUniformMatrix4fv(env->gl.uniform.model, 1, GL_FALSE, camera->model);
	glUniformMatrix4fv(env->gl.uniform.view, 1, GL_FALSE, camera->view);
	glUniformMatrix4fv(env->gl.uniform.projection, 1, GL_FALSE, camera->projection);

	draw_mesh(env);
}

int		 	render(t_env *env)
{
	if (glfwWindowShouldClose(env->gl.window.ptr))
		return (-1);

	glfwPollEvents();

	fps(&env->fps, true);
	events(env);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw(env);

	glfwSwapBuffers(env->gl.window.ptr);
	return (0);
}
