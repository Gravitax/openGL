#include "../../includes/main.h"


int			mtl_newmtl_loader(t_env *env, char **tokens)
{
	t_mtl	new; // New material object

	ft_memset(&new, 0, sizeof(t_mtl));
	if (ft_arrlen(tokens) != 2) // Syntax check
		return (-1);

	if (!(new.name = ft_strdup(tokens[1])) // Copies material name
		// Initializes materials pool if not already up
		|| (env->model.mtls.arr == NULL && dynarray_init(&env->model.mtls, sizeof(t_mtl), 1)))
		return (-1);

	// Moves the new material in the pool
	if (dynarray_push(&env->model.mtls, &new, false))
		return (-1);

	return (0);
}

int			mtl_diffuse_color_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl; // Material to apply color at

	if (ft_arrlen(tokens) != 4) // Syntax check
		return (-1);

	if (env->model.mtls.arr == NULL) // Checks for existing material(s) to apply color at
		return (-1);

	mtl = dyacc(&env->model.mtls, env->model.mtls.nb_cells - 1);

	// Reads color rgb components
	mtl->color.r = (float)atof(tokens[1]);
	mtl->color.g = (float)atof(tokens[2]);
	mtl->color.b = (float)atof(tokens[3]);

	// RGB values check
	if (mtl->color.r < 0.0f || mtl->color.r > 1.0f
		|| mtl->color.g < 0.0f || mtl->color.g > 1.0f
		|| mtl->color.b < 0.0f || mtl->color.b > 1.0f)
		return (-1);

	return (0);
}

int			mtl_alpha_component_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl; // Material to apply color at

	if (ft_arrlen(tokens) != 2) // Syntax check
		return (-1);

	if (env->model.mtls.arr == NULL) // Checks for existing material(s) to apply color at
		return (-1);

	mtl = dyacc(&env->model.mtls, env->model.mtls.nb_cells - 1);

	// Reads alpha value
	mtl->color.a = (float)atof(tokens[1]); // 0 - 1 (1 : no transparency)

	// Checks alpha value
	if (mtl->color.a < 0.0f || mtl->color.a > 1.0f)
		return (-1);

	return (0);
}

static char	*make_texture_path(t_env *env, char *filename)
{
	char		 *path; // Returned string containing texture file path
	unsigned int i = 0;

	while (env->model.obj_path[i] && env->model.obj_path[i] != '/') // Find slash in the string
		i++;

	if (env->model.obj_path[i] == '/') // If there is one, we stop the string after it.
	{
		i++;
		env->model.obj_path[i] = 0;
	}
	else // Else, we set the string at empty to allow us to strjoin in both ways
		env->model.obj_path[0] = 0;

	if (!(path = ft_strjoin(env->model.obj_path, filename)))
		return (NULL);

	return (path);
}

int			mtl_texture_image_loader(t_env *env, char **tokens)
{
	t_mtl			*mtl; // Pointer used for syntaxic contraction
	t_image			*txt; // Texture pointer
	char			*path; // Image file path string
	unsigned int	i = 0;

	if (ft_arrlen(tokens) != 2) // Syntaxic check
		return (-1);

	while (tokens[1][i] && tokens[1][i] != '.') // Find a dot in the filename
		i++;

	if (tokens[1][i] == 0 || ft_strcmp(&tokens[1][i], ".bmp")) // File extension check
		return (-1);

	if (!(path = make_texture_path(env, tokens[1]))) // Create total relative path
		return (-1);

	mtl = dyacc(&env->model.mtls, env->model.mtls.nb_cells - 1);
	txt = &env->model.texture;

	if ((txt->ptr = load_bmp(path, &txt->w, &txt->h)) == NULL) // Load image from path
	{
		free(path);
		return (-1);
	}

	free(path); // Free path string
	return (0);
}
