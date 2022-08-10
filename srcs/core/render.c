#include "main.h"


void		print_matrix(float mat[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("[%.2f]", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n----------------------------\n");
}

void		matrix(t_env *env)
{
	float			mat_flat[16];
	float			model[4][4], view[4][4], projection[4][4], tmp[4][4];

	identity_matrix(model);
	identity_matrix(view);

	update_xrotation_matrix(model, (float)ft_to_radians(112.5));

	translation_matrix(view, (t_vec3d){ 0.f, 0.f, -.75f });

	// env->camera.pitch += 0.1f;

	compute_projection_matrix(env);
	print_matrix(env->camera.cam);

	matrix_flattener(model, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->gl.shader_program, "model"), 1, GL_FALSE, mat_flat);
	matrix_flattener(view, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->gl.shader_program, "view"), 1, GL_FALSE, mat_flat);
	matrix_flattener(env->camera.cam, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->gl.shader_program, "projection"), 1, GL_FALSE, mat_flat);
}

int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->gl.window.ptr))
        return (-1);

    glfw_fps(env, true);

    glfwGetFramebufferSize(env->gl.window.ptr, &env->gl.window.w, &env->gl.window.h);
	glViewport(0, 0, env->gl.window.w, env->gl.window.h);

 	glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < TEXTURES_MAX; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, env->gl.textures[env->texture]);
	}

	matrix(env);

    glDrawElements(GL_TRIANGLES, env->vertices.byte_size, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_LINE, env->vertices.byte_size, GL_UNSIGNED_INT, 0);

	// glUseProgram(env->shader_program);
	// glBindVertexArray(env->gl.vao);

    glfwSwapBuffers(env->gl.window.ptr);
    glfwPollEvents();
    return (0);
}
