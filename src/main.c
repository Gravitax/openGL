#include "main.h"


int         window_open(t_env *env)
{
    int     width, height;

    if (glfwWindowShouldClose(env->window))
        return (-1);
    gl_fps(env, true);
    glfwGetFramebufferSize(env->window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(env->shader_program);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(env->window);
    glfwPollEvents();
    return (0);
}

void        gl_exit(t_env *env)
{
    glDeleteProgram(env->shader_program);
    glDeleteShader(env->shader_vertex);
    glDeleteShader(env->shader_fragment);
    glDeleteBuffers(1, &env->ebo);
    glDeleteBuffers(1, &env->vbo);
    glDeleteVertexArrays(1, &env->vao);
    glfwDestroyWindow(env->window);
    glfwTerminate();
}

int         scop(t_env *env)
{
    if (gl_init(env) < 0)
        return (-1);
    env->time = glfwGetTime();
    while (window_open(env) > -1)
        ;
    gl_exit(env);
    return (0);
}
 
int         main(void)
{
    t_env   env;

    ft_memset(&env, 0, sizeof(t_env));
    exit(scop(&env) < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
