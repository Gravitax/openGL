#include "main.h"


static void shader_create(t_env *env)
{
    // Create and compile the vertex shader
    env->shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(env->shader_vertex, 1, &env->shader_vertex_text, NULL);
    glCompileShader(env->shader_vertex);

    // Create and compile the fragment shader
    env->shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(env->shader_fragment, 1, &env->shader_fragment_text, NULL);
    glCompileShader(env->shader_fragment);
}

static void shader_attach(t_env *env)
{
    // Link the vertex and fragment shader into a shader program
    env->shader_program = glCreateProgram();
    glAttachShader(env->shader_program, env->shader_vertex);
    glAttachShader(env->shader_program, env->shader_fragment);
    glBindFragDataLocation(env->shader_program, 0, "FragColor");
    glLinkProgram(env->shader_program);
    glUseProgram(env->shader_program);
	glDeleteShader(env->shader_vertex);
	glDeleteShader(env->shader_fragment);
}

static void shader_layout(t_env *env)
{
    GLint   position;

    // Specify the layout of the vertex data
    // position
    position = glGetAttribLocation(env->shader_program, "in_position");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, sizeof(t_vec3) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)0);
    // color
    position = glGetAttribLocation(env->shader_program, "in_color");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, sizeof(t_color) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)sizeof(t_vec3));
    // texture
    position = glGetAttribLocation(env->shader_program, "in_texcoord");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, sizeof(t_texture) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)(sizeof(t_vec3) + sizeof(t_color)));
}

int			gl_shaders(t_env *env)
{
    shader_create(env);
    shader_attach(env);
    shader_layout(env);
	return (0);
}
