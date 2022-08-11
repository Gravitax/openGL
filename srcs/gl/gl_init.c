#include "main.h"


static void	gl_shaders(t_gltools *gl)
{
    // Create and compile the vertex shader
    gl->shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(gl->shader_vertex, 1, &gl->shader_vertex_text, NULL);
    glCompileShader(gl->shader_vertex);
    // Create and compile the fragment shader
    gl->shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(gl->shader_fragment, 1, &gl->shader_fragment_text, NULL);
    glCompileShader(gl->shader_fragment);
}

static void	gl_create_program(t_gltools *gl) {
	// Create program
	gl->shader_program = glCreateProgram();
    // Link the vertex and fragment shader into program
    glAttachShader(gl->shader_program, gl->shader_vertex);
    glAttachShader(gl->shader_program, gl->shader_fragment);
	glBindFragDataLocation(gl->shader_program, 0, "FragColor");
	// Link and use program
    glLinkProgram(gl->shader_program);
    glUseProgram(gl->shader_program);
	// Delete used shaders
	glDeleteShader(gl->shader_vertex);
	glDeleteShader(gl->shader_fragment);
}

static void	gl_set_layout(t_gltools *gl)
{
    GLint   position, color, texcoord;

    // position
    position = glGetAttribLocation(gl->shader_program, "in_position");
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, sizeof(t_vec3d) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)0);
    // color
    color = glGetAttribLocation(gl->shader_program, "in_color");
    glEnableVertexAttribArray(color);
    glVertexAttribPointer(color, sizeof(t_color) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)sizeof(t_vec3d));
    // texture
    texcoord = glGetAttribLocation(gl->shader_program, "in_texcoord");
    glEnableVertexAttribArray(texcoord);
    glVertexAttribPointer(texcoord, sizeof(t_texture) * 0.25, GL_FLOAT, GL_FALSE,
        sizeof(t_vertice), (void *)(sizeof(t_vec3d) + sizeof(t_color)));

	glUniform1i(glGetUniformLocation(gl->shader_program, "in_texture"), 0);
}

static void	gl_buffers(t_env *env)
{
	// Create Vertex Array Object
    glGenVertexArrays(1, &env->gl.vao);
    glBindVertexArray(env->gl.vao);
	// Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &env->gl.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, env->gl.vbo);
	glBufferData(GL_ARRAY_BUFFER,
        env->vertices.nb_cells * sizeof(t_vertice),
        env->vertices.arr, GL_STATIC_DRAW);
	// Create an Elements Buffer Object
    glGenBuffers(1, &env->gl.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->gl.ebo);
	// Specify the layout of the vertex data
	gl_set_layout(&env->gl);
}

static void	gl_load_element()
{
    GLuint  elements[] = {
        3, 1, 0,
        2, 3, 0
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

int			gl_init(t_env *env)
{
	gl_shaders(&env->gl);
	gl_create_program(&env->gl);
	gl_buffers(env);
	if (gl_textures(env) < 0)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CW);
	gl_load_element();
	return (0);
}
