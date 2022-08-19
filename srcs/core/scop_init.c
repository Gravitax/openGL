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

static void	cube(t_dynarray *vertices, float x, float y, float z)
{
	//										x			y			z			r		g		b	a		u	v		nx	ny		nz
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
}

static int	load_element(t_env *env)
{
	unsigned int	i, mesh_max;
	t_mesh			*mesh;

	mesh_max = 2;
	if (dynarray_init(&env->mesh, sizeof(t_mesh), mesh_max) < 0)
		return (-1);
	for (i = 0; i < mesh_max; i++) {
		mesh = dyacc(&env->mesh, i);
		if (mesh == NULL)
			continue ;
		if (dynarray_init(&mesh->vertices, sizeof(t_vertice), 36) < 0)
			return (-1);
		cube(&mesh->vertices, 0, i * 4, i * 4);
		mesh->texture = i % 2 ? TEXTURE_NYAN : TEXTURE_DS;
		if (dynarray_push(&env->mesh, mesh, true) < 0)
			return (-1);
	}
	return (0);
}

static void	load_shaders(t_env *env)
{
	env->gl.shader_vertex_text =
		"#version 400\n"
		"\n"
		"layout (location = 0) in vec4	in_position;\n"
		"layout (location = 1) in vec4	in_color;\n"
		"layout (location = 2) in vec2	in_texcoord;\n"
		"layout (location = 3) in vec3	in_normal;\n"
		"\n"
		"uniform mat4	mvp;\n"
		"uniform mat4	model;\n"
		"uniform mat4	view;\n"
		"uniform mat4	projection;\n"
		"\n"
 		"out vec4	Color;\n"
		"out vec4	FragPos;\n"
		"out vec3	Normal;\n"
		"out vec2	Texcoord;\n"
		"\n"
		"void	main()\n"
		"{\n"
		"	Color		= in_color;\n"
		"	FragPos		= in_position * model;\n"
		"	Normal		= in_normal;\n"
		"	Texcoord	= in_texcoord;\n"
		"	gl_Position = in_position * model * view * projection;\n"
		"}\n";
	env->gl.shader_fragment_text =
		"#version 400\n"
		"\n"
		"in vec4	Color;\n"
		"in vec4	FragPos;\n"
		"in vec3	Normal;\n"
		// "in vec2	Texcoord;\n"
		"\n"
		"uniform vec4		light_pos;\n"
		"uniform vec4		light_color;\n"
		// "uniform sampler2D	texture_color;\n"
		"\n"
		"out vec4	FragColor;\n"
		"\n"
		"void	main()\n"
		"{\n"
		// "	FragColor = Color * light_color;\n"
		// "	FragColor = texture(texture_color, Texcoord) * Color;\n"
		// "	FragColor = texture(texture_color, Texcoord);\n"
		"\n"
		"	vec3	n = normalize(Normal);\n"
		"	vec3	light_dir = vec3(normalize(light_pos - FragPos));\n"
		"\n"
		"	float	diff = max(dot(n, light_dir), 0);\n"
		"	vec4	diffuse = light_color * diff;\n"
		"\n"
		"	vec4	ambient = light_color * 0.66f;\n"
		"\n"
		"	FragColor = Color * (ambient + diffuse);\n"
		// "	FragColor = diffuse + ambient;\n"
		// "	FragColor = Color * light_color;\n"
		"\n"
		"}\n";
}

int		 scop_init(t_env *env)
{
	st_env(env, false);
	env->gl.window.fullscreen = false;
	if (load_element(env) < 0 || load_images(env) < 0)
		return (-1);
	if (glfw_init(env) < 0)
		return (-1);
	camera(env);
	load_shaders(env);
	if (gl_init(env) < 0)
		return (-1);
	env->fps.time = glfwGetTime();
	return (0);
}
