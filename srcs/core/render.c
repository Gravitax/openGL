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
	float			tmp1[4][4], tmp2[4][4];

	matrix_identity(tmp1);
	matrix_identity(tmp2);

	matrix_xrotation(env->camera.model, (float)glfwGetTime() / 10 * -1);
	// matrix_zrotation(tmp1, (float)glfwGetTime());
	// matrix_yrotation(tmp2, (float)glfwGetTime());
	// matrix_mult_matrix(tmp1, tmp2, model);

	matrix_view(&env->camera);

	matrix_flattener(env->camera.model, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->gl.shader_program, "model"), 1, GL_FALSE, mat_flat);
	matrix_flattener(env->camera.view, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->gl.shader_program, "view"), 1, GL_FALSE, mat_flat);
	matrix_flattener(tmp1, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->gl.shader_program, "projection"), 1, GL_FALSE, mat_flat);
}

int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->gl.window.ptr))
        return (-1);

    glfw_fps(env, true);

    glfwGetFramebufferSize(env->gl.window.ptr, (int *)&env->gl.window.w, (int *)&env->gl.window.h);
	glViewport(0, 0, (int)env->gl.window.w, (int)env->gl.window.h);

 	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < TEXTURES_MAX; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, env->gl.textures[env->texture]);
	}

	matrix(env);

	// glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, env->vertices.byte_size, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_LINE, env->vertices.byte_size, GL_UNSIGNED_INT, 0);

	// glUseProgram(env->shader_program);
	// glBindVertexArray(env->gl.vao);

    glfwSwapBuffers(env->gl.window.ptr);
    glfwPollEvents();
    return (0);
}
