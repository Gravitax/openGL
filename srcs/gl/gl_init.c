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

static void	gl_layouts(t_gltools *gl)
{
	GLint	position, color, texcoord, normal;

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
	// normal
	normal = glGetAttribLocation(gl->shader_program, "in_normal");
	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, sizeof(vec3) * 0.25, GL_FLOAT, GL_FALSE,
		sizeof(t_vertice), (void *)(sizeof(vec3) + sizeof(t_color) + sizeof(t_texture)));
}

static void	gl_buffers(t_gltools *gl, t_mesh *mesh)
{
	// Create Vertex Array Object
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);
	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER,
		mesh->vertices.nb_cells * sizeof(t_vertice),
		mesh->vertices.arr, GL_STATIC_DRAW);
	// Create an Elements Buffer Object
	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->vertices.byte_size, mesh->vertices.arr, GL_STATIC_DRAW);
	gl_layouts(gl);
	glBindVertexArray(0);
}

static void gl_uniforms(t_env* env)
{
	// get uniforms
	env->gl.uniform.light_pos = glGetUniformLocation(env->gl.shader_program, "light_pos");
	env->gl.uniform.light_color = glGetUniformLocation(env->gl.shader_program, "light_color");
	env->gl.uniform.texture = glGetUniformLocation(env->gl.shader_program, "texture_color");

	env->gl.uniform.mvp = glGetUniformLocation(env->gl.shader_program, "mvp");

	env->gl.uniform.model = glGetUniformLocation(env->gl.shader_program, "model");
	env->gl.uniform.view = glGetUniformLocation(env->gl.shader_program, "view");
	env->gl.uniform.projection = glGetUniformLocation(env->gl.shader_program, "projection");

	// consume uniforms
	glUniform4fv(env->gl.uniform.light_pos, 1, (GLfloat *)&env->camera.light.pos);
	glUniform4fv(env->gl.uniform.light_color, 1, (GLfloat *)&env->camera.light.color);
	glUniform1i(env->gl.uniform.texture, 0);
}

int			gl_init(t_env *env)
{
	t_mesh	*mesh;
	int		i;

	gl_shaders(&env->gl);
	gl_program(&env->gl);
	gl_uniforms(env);
	gl_textures(env);

	i = -1;
	while (++i < env->mesh.nb_cells) {
		mesh = dyacc(&env->mesh, i);
		if(mesh == NULL)
			continue ;
		gl_buffers(&env->gl, mesh);
	}

	//  DEPTH BUFFER
	glEnable(GL_DEPTH_TEST);

	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CW);
	return (0);
}
