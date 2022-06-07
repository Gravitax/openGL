#include "main.h"


int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->window))
        return (-1);
    glfw_fps(env, true);
    glfwGetFramebufferSize(env->window, &env->ww, &env->wh);
	
	glViewport(0, 0, env->ww, env->wh);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(env->window);
    glfwPollEvents();
    return (0);
}
