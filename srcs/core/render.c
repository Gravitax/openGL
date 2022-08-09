#include "main.h"


int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->window))
        return (-1);

    glfw_fps(env, true);

    glfwGetFramebufferSize(env->window, &env->ww, &env->wh);
	glViewport(0, 0, env->ww, env->wh);

 	glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

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
