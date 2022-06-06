#include "main.h"


int         gl_render(t_env *env)
{
    int     width, height;

    if (glfwWindowShouldClose(env->window))
        return (-1);
    gl_fps(env, true);
    glfwGetFramebufferSize(env->window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    // glUseProgram(env->shader_program);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(env->window);
    glfwPollEvents();
    return (0);
}
