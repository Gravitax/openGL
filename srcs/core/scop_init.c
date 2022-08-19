#include "../../includes/main.h"


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

static void	cube(t_dynarray *vertices, float o)
{
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 0.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 2.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + o, 2.0f + o, 0.0f + o, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f }, false);
}

static int	load_element(t_env *env)
{
	unsigned int	i, mesh_max;
	t_mesh			*mesh;

	mesh_max = 10;
	if (dynarray_init(&env->mesh, sizeof(t_mesh), mesh_max) < 0)
		return (-1);
	for (i = 0; i < mesh_max; i++) {
		mesh = dyacc(&env->mesh, i);
		if (mesh == NULL)
			continue ;
		if (dynarray_init(&mesh->vertices, sizeof(t_vertice), 36) < 0)
			return (-1);
		cube(&mesh->vertices, (float)(i * 2));
		mesh->texture = i % 2 ? TEXTURE_DS : TEXTURE_NYAN;
		if (dynarray_push(&env->mesh, mesh, true) < 0)
			return (-1);
	}
	return (0);
}

static void	load_shaders(t_env *env)
{
	env->gl.shader_vertex_text =
		"#version 400\n"
		"layout (location = 0) in vec4 in_position;\n"
		"layout (location = 1) in vec4 in_color;\n"
		"layout (location = 2) in vec2 in_texcoord;\n"
 		// "out vec4 Color;\n"
		"out vec2 Texcoord;\n"
		"uniform mat4 mvp;\n"
		"void main()\n"
		"{\n"
		// "	Color = in_color;\n"
		"	Texcoord = in_texcoord;\n"
		"	gl_Position = in_position * mvp;\n"
		"}\n";
	env->gl.shader_fragment_text =
		"#version 400\n"
		// "in vec4 Color;\n"
		"in vec2 Texcoord;\n"
		"out vec4 FragColor;\n"
		"uniform sampler2D in_texture;\n"
		"void main()\n"
		"{\n"
		// "	FragColor = texture(in_texture, Texcoord) * vec4(255, 255, 255, 0);\n"
		"	FragColor = texture(in_texture, Texcoord);\n"
		"}\n";
}

int		 scop_init(t_env *env)
{
	st_env(env, false);
	if (load_element(env) < 0 || load_images(env) < 0)
		return (-1);
	load_shaders(env);
	env->gl.window.fullscreen = false;
	if (glfw_init(env) < 0 || gl_init(env) < 0)
		return (-1);
	camera(env);
	env->fps.time = glfwGetTime();
	return (0);
}
