#include "main.h"


static int	load_images(t_env *env)
{
	const char		*images_path[TEXTURES_MAX] = {
		"./ressources/images/darksouls.bmp",
		"./ressources/images/nyan.bmp"
	};
	int				i = -1;

	while (++i < TEXTURES_MAX) {
		if (!(env->images[i].img = load_bmp(images_path[i], &env->images[i].w, &env->images[i].h)))
			return (-1);
	}
	return (0);
}

static int	load_rect(t_dynarray *vertices, float x, float y) {
	t_vertice  v;

	// top_left
    v = (t_vertice){
        .pos = (t_vec3){ .x = -0.5f + x, 0.5f + y, 0.f, 1.f },
        .col = (t_color){ 1.f, 0.f, 0.f, 1.f },
        .tex = (t_texture){ 0.f, 1.f }
    };
    if (dynarray_push(vertices, &v, false) < 0)
        return (-1);
    // top_right
    v = (t_vertice){
        (t_vec3){ 0.5f + x, 0.5f + y, 0.f, 1.f },
        (t_color){ 0.f, 1.f, 0.f, 1.f },
		(t_texture){ 1.f, 1.f }
    };
    if (dynarray_push(vertices, &v, false) < 0)
        return (-1);
    // bottom_left
    v = (t_vertice){
        (t_vec3){ -0.5f + x, -0.5f + y, 0.f, 1.f },
        (t_color){ 1.f, 1.f, 1.f, 1.f },
		(t_texture){ 0.f, 0.f }
    };
    if (dynarray_push(vertices, &v, false) < 0)
        return (-1);
    // bottom_right
    v = (t_vertice){
        (t_vec3){ 0.5f + x, -0.5f + y, 0.f, 1.f },
        (t_color){ 0.f, 0.f, 1.f, 1.f },
		(t_texture){ 1.f, 0.f }
    };
    if (dynarray_push(vertices, &v, false) < 0)
        return (-1);
	return (0);
}

static int  load_elements(t_env *env)
{
	if (dynarray_init(&env->vertices, sizeof(t_vertice), 4) < 0)
		return (-1);
	if (load_rect(&env->vertices, 0, 0) < 0)
		return (-1);
    return (0);
}

static void load_shaders(t_env *env)
{
    env->shader_vertex_text =
        "#version 330\n"
		"layout (location = 0) in vec4 in_position;\n"
		"layout (location = 1) in vec4 in_color;\n"
		"layout (location = 2) in vec2 in_texcoord;\n"
 		"out vec4 Color;\n"
        "out vec2 Texcoord;\n"
        "void main()\n"
        "{\n"
        "    Color = in_color;\n"
        "    Texcoord = in_texcoord;\n"
        "    gl_Position = in_position;\n"
        "}\n";
    env->shader_fragment_text =
        "#version 330\n"
		// "in vec4 Color;\n"
        "in vec2 Texcoord;\n"
        "out vec4 FragColor;\n"
        "uniform sampler2D in_texture;\n"
        "void main()\n"
        "{\n"
		// "    FragColor = texture(in_texture_0, Texcoord) * vec4(255, 255, 255, 0);\n"
		"    FragColor = texture(in_texture, Texcoord);\n"
        "}\n";
}

int         scop_init(t_env *env)
{
    st_env(env, false);
    if (load_elements(env) < 0 || load_images(env) < 0)
        return (-1);
    load_shaders(env);
	env->texture = TEXTURE_DS;
	if (glfw_init(env) < 0 || gl_init(env) < 0)
		return (-1);
	env->time = glfwGetTime();
    return (0);
}
