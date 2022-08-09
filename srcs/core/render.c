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
	const float		mat_flat[16];
	float			model[4][4], view[4][4], projection[4][4], tmp[4][4];

	identity_matrix(model);
	identity_matrix(view);

	update_xrotation_matrix(model, -55);

	translation_matrix(view, (t_vec3d){ 0.f, 0.f, -.5f });

	compute_projection_matrix(env);

	matrix_flattener(model, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->shader_program, "model"), 1, GL_FALSE, mat_flat);
	matrix_flattener(view, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->shader_program, "view"), 1, GL_FALSE, mat_flat);
	matrix_flattener(env->camera.cam, mat_flat);
    glUniformMatrix4fv(glGetUniformLocation(env->shader_program, "projection"), 1, GL_FALSE, mat_flat);

	// glUseProgram(env->shader_program);
}

int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->window))
        return (-1);

    glfw_fps(env, true);

    glfwGetFramebufferSize(env->window, &env->ww, &env->wh);
	glViewport(0, 0, env->ww, env->wh);

 	glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

	matrix(env);

	for (int i = 0; i < TEXTURES_MAX; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, env->textures[env->texture]);
	}

    glDrawElements(GL_TRIANGLES, env->vertices.byte_size, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_LINE, env->vertices.byte_size, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(env->window);
    glfwPollEvents();
    return (0);
}
