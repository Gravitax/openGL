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
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.nb_cells);
		glBindVertexArray(0);
	}
}

static void	mat4_view(t_camera *camera)
{
	if (camera->ground_fixed == true)
		camera->pos.y = 0;
	mat4_lookat(camera->view, camera->pos, vec_add(camera->pos, camera->zaxis), camera->yaxis);
	mat4_inverse(camera->view);
}

static void	draw(t_env *env) {
	t_camera		*camera;

	camera = &env->camera;
	mat4_view(camera);

	mat4_identity(env->model.model);
	mat4_translate(env->model.model, env->model.trans.x, env->model.trans.y, env->model.trans.z);

	// mat4	m;
	// vec3	center;

	// mat4_rotate(m, env->model.rot.x, env->model.rot.y, env->model.rot.z);
	// center = mat4_x_vec3(m, env->model.center);
	// center = env->model.center;

	// mat4_translate(env->model.model, -center.x, -center.y, -center.z);
	mat4_rotate(env->model.model, env->model.rot.x, env->model.rot.y, env->model.rot.z);
	// mat4_translate(env->model.model, center.x, center.y, center.z);

	// update camera pos in shaders
	glUniform4fv(env->gl.uniform.light[LIGHT_POSITION], 1, (GLfloat *)&env->camera.pos);

	// update matrices in shaders
	glUniformMatrix4fv(env->gl.uniform.model, 1, GL_FALSE, env->model.model);
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
	events_keyboard(env);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw(env);

	glfwSwapBuffers(env->gl.window.ptr);
	return (0);
}
