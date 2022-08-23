#include "../../includes/main.h"


// Constant array of strings used to store mtl format line identifiers.
static const char	*mtl_lines_ids[MTL_MAX] = {
									  [MTL_COMMENT] = "#",
									  [MTL_NEWMTL] = "newmtl",
									  [MTL_Ns] = "Ns",
									  [MTL_Ka] = "Ka",
									  [MTL_Kd] = "Kd",
									  [MTL_Ks] = "Ks",
									  [MTL_Ke] = "Ke",
									  [MTL_Ni] = "Ni",
									  [MTL_d] = "d",
									  [MTL_ILLUM] = "illum",
									  [MTL_MAP_KD] = "map_Kd"
};

// Function pointer array used to bind a function to each line identifier.
static int	(*mtl_loading_fts[MTL_MAX])(t_env *, char **) = {
									  [MTL_COMMENT] = NULL,
									  [MTL_NEWMTL] = mtl_newmtl_loader,
									  [MTL_Ns] = NULL,
									  [MTL_Ka] = NULL,
									  [MTL_Kd] = mtl_diffuse_color_loader,
									  [MTL_Ks] = NULL,
									  [MTL_Ke] = NULL,
									  [MTL_Ni] = NULL,
									  [MTL_d] = mtl_alpha_component_loader,
									  [MTL_ILLUM] = NULL,
									  [MTL_MAP_KD] = mtl_texture_image_loader
};

static int	mtl_loader(t_env *env, char *line)
{
	char	**tokens;
	int		code;

	// Splits line into words
	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (-1);

	// Identifies line type by iterating through every handled mtl line types.
	for (unsigned int i = 0; i < MTL_MAX; i++)
		if (ft_strcmp(tokens[0], mtl_lines_ids[i]) == 0)
		{
			if (mtl_loading_fts[i]) // If the line's type is handled
			{
				code = mtl_loading_fts[i](env, tokens); // Launch correponding loading function
				ft_arrfree(tokens);
				return (code);
			}
			ft_arrfree(tokens); // Free tokens array
			return (0);
		}

	ft_arrfree(tokens);
	return (-1);
}

static int	load_mtl_file(t_env *env)
{
	char	**lines;
	int		code;

	// Reads file ans splits it in lines
	if ((code = readlines(env->model.obj_path, &lines)) != 0)
		return (code);

	// Iterate through lines to load mtl data
	for (unsigned int i = 0; lines[i]; i++)
		if ((code = mtl_loader(env, lines[i])))
			return (code);

	// Free lines array
	ft_arrfree(lines);
	return (0);
}

int			obj_mtllib_loader(t_env *env, char **tokens)
{
	int	code;

	(void)tokens;

	/* Making new path, assuming that mtl file is named the same as its
	 * corresponding obj file, and is located in the same directory (convention).*/
	ft_strcpy(&env->model.obj_path[ft_strlen(env->model.obj_path) - 4], ".mtl");

	if ((code = load_mtl_file(env)) != 0)
		return (code);
	return (0);
}
