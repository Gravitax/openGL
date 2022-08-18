#include "../../includes/main.h"


static void	mat4_view(t_camera *camera)
{
	mat4_lookat(camera->view, camera->pos, vec_add(camera->pos, camera->zaxis), camera->yaxis);
	mat4_inverse(camera->view);
}

static void	projection(t_gltools *gl, t_camera *camera)
{
	mat4_view(camera);
	mat4_identity(camera->mvp);
	mat4_multiply(camera->mvp, camera->projection);
	mat4_multiply(camera->mvp, camera->view);
	mat4_multiply(camera->mvp, camera->model);
	glUniformMatrix4fv(gl->uniform.mvp, 1, GL_FALSE, camera->mvp);
}

static void	draw(t_env *env) {
	glDrawArrays(GL_TRIANGLES, 0, env->vertices.nb_cells);
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

int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->gl.window.ptr))
        return (-1);

	glfwPollEvents();

    glfwGetFramebufferSize(env->gl.window.ptr, (int *)&env->gl.window.w, (int *)&env->gl.window.h);
	glViewport(0, 0, (int)env->gl.window.w, (int)env->gl.window.h);

	fps(&env->fps, true);
	events(env);
	textures(env->gl.textures, env->texture);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projection(&env->gl, &env->camera);
	draw(env);

    glfwSwapBuffers(env->gl.window.ptr);
    return (0);
}
