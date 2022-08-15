#include "main.h"


static void	mat4_view(t_camera *camera)
{
	t_vec3d	pos;

	pos = mat4_x_vec3d(camera->rot_xyz, camera->pos);
	mat4_lookat(camera->view, pos, vec_add(pos, camera->target), camera->up);
}

static void	matrices(t_gltools *gl, t_camera *camera)
{
	mat4_view(camera);
	mat4_identity(camera->mvp);
	mat4_multiply(camera->mvp, camera->projection);
	mat4_multiply(camera->mvp, camera->view);
	mat4_multiply(camera->mvp, camera->model);
	glUniformMatrix4fv(gl->uniform.mvp, 1, GL_FALSE, camera->mvp);
}

static void	draw(t_env *env) {
	// int	i = 0;

    // while (i < 7)
    // {
    //     mat4_identity(env->camera.model);
	// 	mat4_translate(env->camera.model, env->cube_positions[i].x, env->cube_positions[i].y, env->cube_positions[i].z);
    //     glUniformMatrix4fv(env->gl.uniform.model, 1, GL_FALSE, env->camera.model);
    //     glDrawArrays(GL_TRIANGLES, 0, 36);
	// 	++i;
    // }

	glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, env->vertices.byte_size, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_LINE, env->vertices.byte_size, GL_UNSIGNED_INT, 0);
}

int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->gl.window.ptr))
        return (-1);

    glfw_fps(&env->fps, true);
	glfwPollEvents();
	events(env);

    glfwGetFramebufferSize(env->gl.window.ptr, (int *)&env->gl.window.w, (int *)&env->gl.window.h);
	glViewport(0, 0, (int)env->gl.window.w, (int)env->gl.window.h);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < TEXTURES_MAX; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, env->gl.textures[env->texture]);
	}

	matrices(&env->gl, &env->camera);

	// glUseProgram(env->gl.shader_program);
    // glBindVertexArray(env->gl.vao);

	draw(env);

    glfwSwapBuffers(env->gl.window.ptr);
    return (0);
}
