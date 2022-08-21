#include "../../includes/main.h"


static void	textures(GLuint *textures, int id)
{
	int	i;

	i = -1;
	while (++i < TEXTURE_MAX) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[id]);
	}
}

static void	draw_mesh(t_env *env)
{
	t_mesh	*mesh;
	int		i;

	i = -1;
	while (++i < env->model.mesh.nb_cells) {
		mesh = dyacc(&env->model.mesh, i);
		if (mesh == NULL)
			continue ;
		textures(env->gl.textures, mesh->texture);
		glBindVertexArray(mesh->vao);

		// glDrawElements(GL_TRIANGLES, (GLsizei)env->parser.element_size / (GLsizei)sizeof(float), GL_UNSIGNED_INT, 0);

		glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.nb_cells);
		glBindVertexArray(0);
	}
}

static void	set_uniforms(t_env *env)
{
	glUniform1f(env->gl.uniform.progress, env->animation.progress);

	// update camera pos in shaders
	glUniform4fv(env->gl.uniform.light[LIGHT_POSITION], 1, (GLfloat *)&env->camera.pos);

	// update matrices in shaders
	glUniformMatrix4fv(env->gl.uniform.model, 1, GL_FALSE, env->model.model);
	glUniformMatrix4fv(env->gl.uniform.view, 1, GL_FALSE, env->camera.view);
	glUniformMatrix4fv(env->gl.uniform.projection, 1, GL_FALSE, env->camera.projection);
}

static void	mat4_view(t_camera *camera)
{
	if (camera->ground_fixed == true)
		camera->pos.y = 0;
	mat4_lookat(camera->view, camera->pos, vec_add(camera->pos, camera->zaxis), camera->yaxis);
	mat4_inverse(camera->view);
}

static void	mat4_model(t_model *model)
{
	mat4_identity(model->model);
	mat4_translate(model->model, model->trans.x, model->trans.y, model->trans.z);
	mat4_rotate(model->model, model->rot.x, model->rot.y, model->rot.z);
	mat4_scale(model->model, model->scale);
}

static void	mat4_mvp(t_env *env)
{
	mat4_model(&env->model);
	mat4_view(&env->camera);
	mat4_projection(env->camera.projection, env->camera.fov, env->camera.near, env->camera.far, env->camera.ratio);
}

static void	update_animation(t_env *env)
{
	env->animation.progress += env->animation.step;
	glUniform1f(env->gl.uniform.progress, env->animation.progress);
	if (env->animation.progress >= 1 || env->animation.progress <= 0)
		env->animation.active = false;
}

static void	draw(t_env *env) {
	if (env->animation.active == true)
		update_animation(env);
	mat4_mvp(env);
	set_uniforms(env);
	draw_mesh(env);
}

int		 	render(t_env *env)
{
	if (glfwWindowShouldClose(env->gl.window.ptr))
		return (-1);

	glfwPollEvents();

	fps(&env->fps, true);
	events_keyboard(env);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw(env);

	glfwSwapBuffers(env->gl.window.ptr);
	return (0);
}
