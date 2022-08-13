#include "main.h"


void		matrix(t_env *env)
{

	// const float radius = 10.0f;
	// env->camera.pos.x = sin(glfwGetTime()) * radius;
	// env->camera.pos.z = cos(glfwGetTime()) * radius;

	mat4_identity(env->camera.model);
	mat4_translate(env->camera.model, 0, 0, 1);
	// mat4_rotate(env->camera.model,
	// 	(float)ft_to_radians(env->camera.pitch), (float)ft_to_radians(env->camera.yaw), (float)ft_to_radians(env->camera.roll),
	// 	(t_vec3d){ env->camera.pos.x, env->camera.pos.y, env->camera.pos.z });
	glUniformMatrix4fv(env->gl.uniform.model, 1, GL_FALSE, env->camera.model);
	
	mat4_view(&env->camera);
	glUniformMatrix4fv(env->gl.uniform.view, 1, GL_FALSE, env->camera.view);

	// mat4_identity(env->camera.mvp);
	// mat4_multiply(env->camera.mvp, env->camera.model);
	// mat4_multiply(env->camera.mvp, env->camera.view);
	// mat4_multiply(env->camera.mvp, env->camera.projection);

	// glUniformMatrix4fv(env->gl.uniform.mvp, 1, GL_FALSE, env->camera.mvp);
}

static void	draw(t_env *env) {
	// int	i = 0;

    // while (i < 7)
    // {
    //     mat4_identity(env->camera.model);
	// 	mat4_translate(env->camera.model, env->cube_positions[i].x, env->cube_positions[i].y, env->cube_positions[i].z + 1);
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

	matrix(env);

	// glUseProgram(env->gl.shader_program);
    // glBindVertexArray(env->gl.vao);

	draw(env);

    glfwSwapBuffers(env->gl.window.ptr);
    return (0);
}
