#include "main.h"


static int	load_images(t_env *env)
{
	const char		*images_path[TEXTURES_MAX] = {
		"./ressources/images/darksouls.bmp",
		"./ressources/images/nyan.bmp"
	};
	int				i = -1;

	while (++i < TEXTURES_MAX) {
		if (!(env->images[i].ptr = load_bmp(images_path[i], &env->images[i].w, &env->images[i].h)))
			return (-1);
	}
	return (0);
}

static void	cube(t_dynarray *vertices)
{
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
}

static int	load_element(t_env *env)
{
	t_vertice v;

	if (dynarray_init(&env->vertices, sizeof(t_vertice), 36) < 0)
		return (-1);
	cube(&env->vertices);
	return (0);
}

static void	load_shaders(t_env *env)
{
	env->gl.shader_vertex_text =
		"#version 330\n"
		"layout (location = 0) in vec4 in_position;\n"
		"layout (location = 1) in vec4 in_color;\n"
		"layout (location = 2) in vec2 in_texcoord;\n"
 		// "out vec4 Color;\n"
		"out vec2 Texcoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		// "	Color = in_color;\n"
		"	Texcoord = in_texcoord;\n"
		"	gl_Position = model * view * projection * in_position;\n"
		// "	gl_Position.x /= gl_Position.w;\n"
		// "	gl_Position.y /= gl_Position.w;\n"
		// "	gl_Position.z /= gl_Position.w;\n"
		// "	gl_Position.w /= gl_Position.w;\n"
		"}\n";
	env->gl.shader_fragment_text =
		"#version 330\n"
		// "in vec4 Color;\n"
		"in vec2 Texcoord;\n"
		"out vec4 FragColor;\n"
		"uniform sampler2D in_texture;\n"
		"void main()\n"
		"{\n"
		// "	FragColor = texture(in_texture_0, Texcoord) * vec4(255, 255, 255, 0);\n"
		"	FragColor = texture(in_texture, Texcoord);\n"
		"}\n";
}

int		 scop_init(t_env *env)
{
	st_env(env, false);
	if (load_element(env) < 0 || load_images(env) < 0)
		return (-1);
	load_shaders(env);
	env->texture = TEXTURE_DS;
	if (glfw_init(env) < 0 || gl_init(env) < 0)
		return (-1);
	env->time = glfwGetTime();
	init_camera(env);
	return (0);
}
