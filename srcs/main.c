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
 
int		 	main(void)
{
	t_env   env;

	ft_memset(&env, 0, sizeof(t_env));
	exit(scop(&env) < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
