#include "../../includes/main.h"


static void	mat4_view(t_camera *camera)
{
	if (camera->ground_fixed == true)
		camera->pos.y = 0;
	mat4_lookat(camera->view, camera->pos, vec_add(camera->pos, camera->zaxis), camera->yaxis);
	mat4_inverse(camera->view);
}

static void	draw(t_env *env) {
	t_camera		*camera = &env->camera;
	mat4			tmp;
	unsigned int	i;

	mat4_view(camera);

	mat4_identity(camera->mvp);
	mat4_multiply(camera->mvp, camera->projection);
	mat4_multiply(camera->mvp, camera->view);

	for (i = 0; i < 7; i++) {
		mat4_identity(camera->model);
		mat4_translate(camera->model, env->pos[i].x, env->pos[i].y, env->pos[i].z);
		ft_memcpy(tmp, camera->mvp, sizeof(mat4));
		mat4_multiply(tmp, camera->model);
		glUniformMatrix4fv(env->gl.uniform.mvp, 1, GL_FALSE, tmp);
		glDrawArrays(GL_TRIANGLES, 0, env->vertices.nb_cells);
	}

	// glDrawArrays(GL_TRIANGLES, 0, env->vertices.nb_cells);
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

static void	textures(GLuint *textures, int id)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_MAX) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[id]);
	}
}

int		 	render(t_env *env)
{
	if (glfwWindowShouldClose(env->gl.window.ptr))
		return (-1);

	glfwPollEvents();

	fps(&env->fps, true);
	events(env);
	textures(env->gl.textures, env->texture);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw(env);

	glfwSwapBuffers(env->gl.window.ptr);
	return (0);
}
