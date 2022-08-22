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
	glAttachShader(gl->shader_program, gl->shader_geometry);
	glAttachShader(gl->shader_program, gl->shader_fragment);
	glBindFragDataLocation(gl->shader_program, 0, "FragColor");
	// Link and use program
	glLinkProgram(gl->shader_program);
	glUseProgram(gl->shader_program);
}

static void	gl_layouts(t_gltools *gl)
{
	GLint	position, color, texcoord, normal;

	// Specify the layout of the vertex data
	// position
	// position = glGetAttribLocation(gl->shader_program, "in_position");
	// glEnableVertexAttribArray(position);
	// glVertexAttribPointer(position, sizeof(vec3) * 0.25, GL_FLOAT, GL_FALSE,
	// 	sizeof(t_vertice), (void *)0);
	// // color
	// color = glGetAttribLocation(gl->shader_program, "in_color");
	// glEnableVertexAttribArray(color);
	// glVertexAttribPointer(color, sizeof(t_color) * 0.25, GL_FLOAT, GL_FALSE,
	// 	sizeof(t_vertice), (void *)sizeof(vec3));
	// // texture
	// texcoord = glGetAttribLocation(gl->shader_program, "in_texcoord");
	// glEnableVertexAttribArray(texcoord);
	// glVertexAttribPointer(texcoord, sizeof(t_texture) * 0.25, GL_FLOAT, GL_FALSE,
	// 	sizeof(t_vertice), (void *)(sizeof(vec3) + sizeof(t_color)));
	// // normal
	// normal = glGetAttribLocation(gl->shader_program, "in_normal");
	// glEnableVertexAttribArray(normal);
	// glVertexAttribPointer(normal, sizeof(vec3) * 0.25, GL_FLOAT, GL_FALSE,
	// 	sizeof(t_vertice), (void *)(sizeof(vec3) + sizeof(t_color) + sizeof(t_texture)));

	// position
	position = glGetAttribLocation(gl->shader_program, "in_position");
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 4, (void *)0);
	glEnableVertexAttribArray(position);

	// color
	color = glGetAttribLocation(gl->shader_program, "in_color");
	glVertexAttribPointer(color, 1, GL_FLOAT, GL_FALSE,
		sizeof(float) * 4, (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(color);
}

static void	gl_buffers(t_env *env, t_gltools *gl, t_mesh *mesh)
{
	// VAO -- Create Vertex Array Object
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);
	// VBO -- Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	glBufferData(GL_ARRAY_BUFFER,
		env->parser.vertex_size,
		env->parser.vertex, GL_STATIC_DRAW);

	// EBO -- Create an Elements Buffer Object
	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

	// TEST =========================
	// GLuint  elements[] = {
	// 	3, 1, 0,
	// 	2, 3, 0
	// };

	// env->parser.element = ft_memalloc(sizeof(elements));
	// ft_memcpy(env->parser.element, elements, sizeof(elements));
	// env->parser.element_size = sizeof(elements);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->parser.element_size, env->parser.element, GL_STATIC_DRAW);


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
	while (++i < env->model.mesh.nb_cells) {
		mesh = dyacc(&env->model.mesh, i); 
		if(mesh == NULL)
			continue ;
		gl_buffers(env, &env->gl, mesh);
	}

	//  DEPTH BUFFER
	glEnable(GL_DEPTH_TEST);

	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CCW);
	return (0);
}
