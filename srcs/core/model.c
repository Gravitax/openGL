#include "../../includes/main.h"


int			model(t_env *env)
{
	if (load_obj_file(env, env->model.obj_path) < 0)
		return (-1);
	env->model.scale = 1;
	return (0);
}
