#include "../../includes/main.h"


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

static void	gl_program(t_gltools *gl) {
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
}

static void gl_uniforms(t_env* env)
{
	// get uniforms
	env->gl.uniform.texture = glGetUniformLocation(env->gl.shader_program, "in_texture");
	env->gl.uniform.mvp = glGetUniformLocation(env->gl.shader_program, "mvp");

	// consume texture uniforms
	glUniform1i(env->gl.uniform.texture, 0);
}

static void	gl_layouts(t_gltools *gl)
{
	GLint   position, color, texcoord;

	// Specify the layout of the vertex data
	// position
	position = glGetAttribLocation(gl->shader_program, "in_position");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, sizeof(vec3) * 0.25, GL_FLOAT, GL_FALSE,
		sizeof(t_vertice), (void *)0);
	// color
	color = glGetAttribLocation(gl->shader_program, "in_color");
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, sizeof(t_color) * 0.25, GL_FLOAT, GL_FALSE,
		sizeof(t_vertice), (void *)sizeof(vec3));
	// texture
	texcoord = glGetAttribLocation(gl->shader_program, "in_texcoord");
	glEnableVertexAttribArray(texcoord);
	glVertexAttribPointer(texcoord, sizeof(t_texture) * 0.25, GL_FLOAT, GL_FALSE,
		sizeof(t_vertice), (void *)(sizeof(vec3) + sizeof(t_color)));
}

static void	gl_load_element(t_env *env)
{
	GLuint  elements[] = {
		3, 1, 0,
		2, 3, 0
	};

	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->vertices.byte_size, env->vertices.arr, GL_STATIC_DRAW);
}

int			gl_init(t_env *env)
{
	gl_shaders(&env->gl);
	gl_program(&env->gl);
	gl_buffers(env);
	gl_layouts(&env->gl);
	gl_uniforms(env);
	gl_textures(env);
	//  DEPTH BUFFER
	glEnable(GL_DEPTH_TEST);
	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CW);
	gl_load_element(env);
	return (0);
}
