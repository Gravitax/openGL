#include "main.h"


int         window_open(t_env *env)
{
    float   ratio;
    int     width, height;
    mat4x4  m, p, mvp;

    if (glfwWindowShouldClose(env->window))
        return (-1);
    gl_fps(env, true);
    glfwGetFramebufferSize(env->window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    ratio = width / (float)height;

    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    GLint   mvp_location = glGetUniformLocation(env->shader_program, "MVP");

    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);

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
