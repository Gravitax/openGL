#include "../../includes/main.h"


static void	gl_shaders(t_gltools *gl)
{
	// Create and compile the vertex shader
	gl->shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gl->shader_vertex, 1, &gl->shader_vertex_text, NULL);
	glCompileShader(gl->shader_vertex);
	// Create and compile the fragment shader
	gl->shader_geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gl->shader_geometry, 1, &gl->shader_geometry_text, NULL);
	glCompileShader(gl->shader_geometry);
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
	// glAttachShader(gl->shader_program, gl->shader_geometry);
	glAttachShader(gl->shader_program, gl->shader_fragment);
	glBindFragDataLocation(gl->shader_program, 0, "FragColor");
	// Link and use program
	glLinkProgram(gl->shader_program);
	glUseProgram(gl->shader_program);
}

static void	gl_layouts(t_gltools *gl)
{
	// Specify the layout of the vertex data
	// id ptr, size, GL_FLOAT, GL_FALSE, totalsize, start pos
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(t_stride), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(t_stride), (void *)sizeof(vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_stride), (void *)(sizeof(vec3) + sizeof(t_color)));
	glEnableVertexAttribArray(2);
}

static void	gl_buffers(t_gltools *gl, t_mesh *mesh)
{
	// VAO -- Create Vertex Array Object
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);
	// VBO -- Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	GLsizeiptr	size;

	size = (GLsizeiptr)sizeof(t_stride) * mesh->vertices.nb_cells;
	glBufferData(GL_ARRAY_BUFFER, size, mesh->vertices.arr, GL_STATIC_DRAW);

	// EBO -- Create an Elements Buffer Object
	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

	size = (GLsizeiptr)mesh->faces.nb_cells * (GLsizeiptr)sizeof(uint32_t) * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, mesh->faces.arr, GL_STATIC_DRAW);

	gl_layouts(gl);
	glBindVertexArray(0);
}

static void gl_uniforms(t_env* env)
{
	// get uniforms
	env->gl.uniform.progress = glGetUniformLocation(env->gl.shader_program, "progress");
	env->gl.uniform.campos = glGetUniformLocation(env->gl.shader_program, "campos");
	env->gl.uniform.texture = glGetUniformLocation(env->gl.shader_program, "texture_color");

	env->gl.uniform.model = glGetUniformLocation(env->gl.shader_program, "model");
	env->gl.uniform.view = glGetUniformLocation(env->gl.shader_program, "view");
	env->gl.uniform.projection = glGetUniformLocation(env->gl.shader_program, "projection");

	env->gl.uniform.light[LIGHT_ACTIVE] = glGetUniformLocation(env->gl.shader_program, "light.is_active");
	env->gl.uniform.light[LIGHT_POSITION] = glGetUniformLocation(env->gl.shader_program, "light.pos");
	env->gl.uniform.light[LIGHT_DIRECTION] = glGetUniformLocation(env->gl.shader_program, "light.dir");
	env->gl.uniform.light[LIGHT_COLOR] = glGetUniformLocation(env->gl.shader_program, "light.color");
	env->gl.uniform.light[LIGHT_AMBIENT] = glGetUniformLocation(env->gl.shader_program, "light.ambient");
	env->gl.uniform.light[LIGHT_DIFFUSE] = glGetUniformLocation(env->gl.shader_program, "light.diffuse");
	env->gl.uniform.light[LIGHT_SPECULAR] = glGetUniformLocation(env->gl.shader_program, "light.specular");

	// consume uniforms
	glUniform4fv(env->gl.uniform.campos, 1, (GLfloat *)&env->camera.pos);
	glUniform1i(env->gl.uniform.texture, 0);

	glUniform4fv(env->gl.uniform.light[LIGHT_ACTIVE], 1, (GLfloat *)&env->light.active);
	glUniform4fv(env->gl.uniform.light[LIGHT_POSITION], 1, (GLfloat *)&env->light.pos);
	glUniform4fv(env->gl.uniform.light[LIGHT_DIRECTION], 1, (GLfloat *)&env->light.dir);
	glUniform4fv(env->gl.uniform.light[LIGHT_COLOR], 1, (GLfloat *)&env->light.color);
	glUniform4fv(env->gl.uniform.light[LIGHT_AMBIENT], 1, (GLfloat *)&env->light.ambient);
	glUniform4fv(env->gl.uniform.light[LIGHT_DIFFUSE], 1, (GLfloat *)&env->light.diffuse);
	glUniform4fv(env->gl.uniform.light[LIGHT_SPECULAR], 1, (GLfloat *)&env->light.specular);
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
	while (++i < env->model.meshs.nb_cells) {
		mesh = dyacc(&env->model.meshs, i); 
		if(mesh == NULL)
			continue ;
		gl_buffers(&env->gl, mesh);
	}

	//  DEPTH BUFFER
	glEnable(GL_DEPTH_TEST);

	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CCW);
	return (0);
}
