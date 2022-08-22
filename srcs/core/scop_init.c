#include "../../includes/main.h"


static int	images(t_env *env)
{
	const char		*images_path[TEXTURE_MAX] = {
		"./ressources/images/texture.bmp",
		"./ressources/images/darksouls.bmp",
		"./ressources/images/nyan.bmp"
	};
	int				i = -1;

	while (++i < TEXTURE_MAX) {
		if (!(env->images[i].ptr = load_bmp(images_path[i], &env->images[i].w, &env->images[i].h)))
			return (-1);
	}
	return (0);
}

static void	light(t_light *light)
{
	light->active = false;
	light->pos = (vec3){ -10, 10, -10 };
	light->dir = (vec3){ -0.2f, -1.0f, -0.3f };
	light->color = (vec3){ 1, 1, 1, 1 };
	light->ambient = (vec3){ 0.4f, 0.4f, 0.4f };
	light->diffuse = (vec3){ 0.75f, 0.75f, 0.75f };
	light->specular = (vec3){ 1, 1, 1 };
}

int			scop_init(t_env *env)
{
	st_env(env, false);
	env->gl.window.fullscreen = false;
	env->animation.step = -0.1f;
	if (model(env) < 0 || images(env) < 0 || glfw_init(env) < 0)
		return (-1);
	if (parse_obj(env, "./ressources/42.obj") < 0)
		return (-1);
	camera(env);
	light(&env->light);
	events(env);
	shaders(&env->gl);
	if (gl_init(env) < 0)
		return (-1);
	env->fps.time = glfwGetTime();
	return (0);
}
