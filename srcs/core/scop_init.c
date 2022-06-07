#include "main.h"


static int  load_square(t_env *env)
{
    t_vertices  v;

    if (dynarray_init(&env->vertices, sizeof(t_vertices), 4) < 0)
        return (-1);
    // top_left
    v = (t_vertices){
        (t_vec3){ -0.5f, 0.5f, 0.f, 1.f },
        (t_color){ 1.f, 0.f, 0.f, 1.f },
		// (t_texture){ 0.f, 0.f }
        (t_texture){ 1.f, 1.f }
    };
    if (dynarray_push(&env->vertices, &v, false) < 0)
        return (-1);
    // top_right
    v = (t_vertices){
        (t_vec3){ 0.5f, 0.5f, 0.f, 1.f },
        (t_color){ 0.f, 1.f, 0.f, 1.f },
        // (t_texture){ 1.f, 0.f }
		(t_texture){ 0.f, 1.f }
    };
    if (dynarray_push(&env->vertices, &v, false) < 0)
        return (-1);
    // bottom_left
    v = (t_vertices){
        (t_vec3){ -0.5f, -0.5f, 0.f, 1.f },
        (t_color){ 1.f, 1.f, 1.f, 1.f },
        // (t_texture){ 0.f, 1.f }
		(t_texture){ 1.f, 0.f }
    };
    if (dynarray_push(&env->vertices, &v, false) < 0)
        return (-1);
    // bottom_right
    v = (t_vertices){
        (t_vec3){ 0.5f, -0.5f, 0.f, 1.f },
        (t_color){ 0.f, 0.f, 1.f, 1.f },
        // (t_texture){ 1.f, 1.f }
		(t_texture){ 0.f, 0.f }
    };
    if (dynarray_push(&env->vertices, &v, false) < 0)
        return (-1);
    return (0);
}

static void shader_init(t_env *env)
{
    env->shader_vertex_text =
        "#version 330\n"
        "in vec4 position;\n"
        "in vec4 color;\n"
        "in vec2 texcoord;\n"
        "out vec4 Color;\n"
        "out vec2 Texcoord;\n"
        "void main()\n"
        "{\n"
        "    Color = color;\n"
        "    Texcoord = texcoord;\n"
        "    gl_Position = position;\n"
        "}\n";
    env->shader_fragment_text =
        "#version 330\n"
        // "in vec4 Color;\n"
        "in vec2 Texcoord;\n"
        "out vec4 vColor;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        // "    vColor = texture(tex, Texcoord) * Color;\n"
        "    vColor = texture(tex, Texcoord);\n"
        // "    vColor = Color;\n"
        "}\n";
}

int         scop_init(t_env *env)
{
    st_env(env, false);
    if (load_square(env) < 0)
        return (-1);
    shader_init(env);
	if (glfw_init(env) < 0 || gl_init(env) < 0)
		return (-1);
    return (0);
}
