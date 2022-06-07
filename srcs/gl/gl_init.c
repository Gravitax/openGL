#include "main.h"


static void gl_vobjects(t_env *env)
{
    GLuint  elements[] = {
        0, 1, 3,
        0, 2, 3
    };

    // Create Vertex Array Object
    glGenVertexArrays(1, &env->vao);
    glBindVertexArray(env->vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &env->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
    glBufferData(GL_ARRAY_BUFFER,
        env->vertices.nb_cells * sizeof(t_vertices),
        env->vertices.arr, GL_STATIC_DRAW);

    // Create an Elements Buffer Object
    glGenBuffers(1, &env->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

int		gl_init(t_env *env)
{
	gl_vobjects(env);
    if (gl_shaders(env) < 0 || gl_textures(env) < 0)
		return (-1);
	return (0);
}
