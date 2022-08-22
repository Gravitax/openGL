#include "../../includes/main.h"


static int	pitriche(t_env *env)
{
	t_mesh	*mesh;

	if (dynarray_init(&env->model.meshs, sizeof(t_mesh), 1) < 0)
		return (-1);
	mesh = dyacc(&env->model.meshs, 0);
	if (mesh == NULL)
		return (-1);
	if (dynarray_push(&env->model.meshs, mesh, true) < 0)
		return (-1);
	if (parse_obj(env, "./resources/teapot.obj") < 0)
		return (-1);
	return (0);
}

static int	gedemais(t_env *env, t_model *model)
{
	if (load_obj_file(env, "./resources/42.obj") < 0)
		return (-1);
	return (0);
}

int			model(t_env *env)
{
	if (pitriche(env) < 0)
		return (-1);

	// if (gedemais(env, &env->model) < 0)
	// 	return (-1);

	env->model.scale = 1;
	return (0);
}
