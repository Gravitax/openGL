#include "main.h"


int         scop(t_env *env)
{
    if (env_init(env) < 0 || glfw_init(env) < 0 || gl_init(env) < 0)
    {
        scop_exit();
        return (-1);
    }
    env->time = glfwGetTime();
    while (render(env) > -1)
        ;
    scop_exit();
    return (0);
}
 
int         main(void)
{
    t_env   env;

    ft_memset(&env, 0, sizeof(t_env));
    exit(scop(&env) < 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
