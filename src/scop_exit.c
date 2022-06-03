#include "main.h"


static void gl_exit(t_env *env)
{
    glDeleteTextures(1, &env->tex);
    glDeleteShader(env->shader_vertex);
    glDeleteShader(env->shader_fragment);
    glDeleteProgram(env->shader_program);
    glDeleteBuffers(1, &env->ebo);
    glDeleteBuffers(1, &env->vbo);
    glDeleteVertexArrays(1, &env->vao);
    glfwDestroyWindow(env->window);
    glfwTerminate();
}

static void env_free(t_env *env)
{
    dynarray_free(&env->vertices);
    free(env->img);
}

void        scop_exit(t_env *env)
{
    gl_exit(env);
    env_free(env);
}
