#include "main.h"


t_env   *singleton(t_env *env)
{
    static t_env    *save = NULL;

    if (save == NULL && env)
        save = env;
    return (save);
}
