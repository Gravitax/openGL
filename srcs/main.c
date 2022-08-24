#include "../includes/main.h"


static int	scop(t_env *env)
{
	if (scop_init(env) < 0)
	{
		scop_exit();
		return (-1);
	}
	while (render(env) > -1)
		;
	scop_exit();
	return (0);
}
 
int		 	main(int ac, char **av)
{
	t_env   env;
	int		code, length;

	code = -1;
	if (ac == 2 && (length = ft_strlen(av[1])) < 256) {
		ft_memset(&env, 0, sizeof(t_env));
		ft_memcpy(env.model.obj_path, av[1], length);
		code = scop(&env);
	}
	return (code == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
