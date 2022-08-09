#include "main.h"


static void	gl_shaders(t_env *env)
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

static void	gl_create_program(t_env *env) {
	// Create program
	env->shader_program = glCreateProgram();
    // Link the vertex and fragment shader into program
    glAttachShader(env->shader_program, env->shader_vertex);
    glAttachShader(env->shader_program, env->shader_fragment);
	glBindFragDataLocation(env->shader_program, 0, "FragColor");
	// Link and use program
    glLinkProgram(env->shader_program);
    glUseProgram(env->shader_program);
	// Delete used shaders
	glDeleteShader(env->shader_vertex);
	glDeleteShader(env->shader_fragment);
}

static void	gl_set_layout(t_env *env)
{
    GLint   position, color, texcoord;

    // position
    position = glGetAttribLocation(env->shader_program, "in_position");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, sizeof(t_vec3) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)0);
    // color
    color = glGetAttribLocation(env->shader_program, "in_color");
    glEnableVertexAttribArray(color);
    glVertexAttribPointer(color, sizeof(t_color) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)sizeof(t_vec3));
    // texture
    texcoord = glGetAttribLocation(env->shader_program, "in_texcoord");
    glEnableVertexAttribArray(texcoord);
    glVertexAttribPointer(texcoord, sizeof(t_texture) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)(sizeof(t_vec3) + sizeof(t_color)));

	glUniform1i(glGetUniformLocation(env->shader_program, "in_texture"), 0);
}

static void	gl_buffers(t_env *env)
{
	// Create Vertex Array Object
    glGenVertexArrays(1, &env->vao);
    glBindVertexArray(env->vao);
	// Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &env->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER,
        env->vertices.nb_cells * sizeof(t_vertice),
        env->vertices.arr, GL_STATIC_DRAW);
	// Create an Elements Buffer Object
    glGenBuffers(1, &env->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	// Specify the layout of the vertex data
	gl_set_layout(env);
	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CW);
}

static void	gl_load_element(t_env *env)
{
    GLuint  elements[] = {
        3, 1, 0,
        2, 3, 0
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

int			gl_init(t_env *env)
{
	gl_shaders(env);
	gl_create_program(env);
	gl_buffers(env);
	if (gl_textures(env) < 0)
		return (-1);
	gl_load_element(env);
	return (0);
}
