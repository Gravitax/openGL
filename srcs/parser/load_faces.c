#include "../../includes/main.h"


uint32_t	*used_mtl(void)
{
	static uint32_t	used_mtl = UINT_MAX;

	return (&used_mtl);
}

static int	assign_face_indexes(t_face *new, char **tokens, int indexes[3])
{
	char	**subs[3];
	int		n[3];

	for (unsigned int i = 0; i < 3; i++)
	{
		if (!(subs[i] = ft_strsplit(tokens[indexes[i]], "/")))
			return (-1);

		n[i] = ft_arrlen(subs[i]);
		if (i > 0 && n[i] != n[i - 1])
			return (-1);
	}

	// Reads the faces components (indexes in vertexs pool)
	new->a = (uint32_t)ft_atoi(subs[0][0]) - 1;
	new->b = (uint32_t)ft_atoi(subs[1][0]) - 1;
	new->c = (uint32_t)ft_atoi(subs[2][0]) - 1;

	if (n[0] < 2)
		return (0);

	new->va = (uint32_t)ft_atoi(subs[0][1]) - 1;
	new->vb = (uint32_t)ft_atoi(subs[1][1]) - 1;
	new->vc = (uint32_t)ft_atoi(subs[2][1]) - 1;

	return (0);
}

static int	check_face_indexes(t_env *env, t_face new)
{
	// Checks if vertexs indexes values are coherent with the rest of the file
	if (new.a >= (unsigned int)env->model.vertexs.nb_cells
		|| new.b >= (unsigned int)env->model.vertexs.nb_cells
		|| new.c >= (unsigned int)env->model.vertexs.nb_cells)
		return (-1);

	if (env->model.vertexs_txt.nb_cells > 0)
		if (new.va >= (unsigned int)env->model.vertexs_txt.nb_cells
			|| new.vb >= (unsigned int)env->model.vertexs_txt.nb_cells
			|| new.vc >= (unsigned int)env->model.vertexs_txt.nb_cells)
			return (-1);

	return (0);
}

static int	split_quad(t_env *env, t_mesh *parent, uint32_t a_index, char **tokens)
{
	t_face		news[2];
	uint32_t	b_index = a_index + 1;

	ft_memset(news, 0, sizeof(t_face) * 2);
	// Polygon faces indexes assignment
	if (assign_face_indexes(&news[0], tokens, (int[3]){1, 2, 3})
		|| assign_face_indexes(&news[1], tokens, (int[3]){1, 3, 4}))
		return (-1);

	// Checks indexes values
	if (check_face_indexes(env, news[0]) != 0
		|| check_face_indexes(env, news[1]) != 0)
		return (-1);

	// Moves new faces into pool
	if (dynarray_push(&env->model.faces, &news[0], false)
		|| dynarray_push(&env->model.faces, &news[1], false))
		return (-1);

	// Moves faces indexes into parent mesh
	if (dynarray_push(&parent->vertices, &a_index, false)
		|| dynarray_push(&parent->vertices, &b_index, false))
		return (-1);

	return (0);
}

static int	load_face(t_env *env, char **tokens, t_mesh *parent, uint32_t face_index)
{
	t_face	new;

	ft_memset(&new, 0, sizeof(t_face));

	assign_face_indexes(&new, tokens, (int[3]){1, 2, 3});

	// Moves instance in the pool.
	if (dynarray_push(&env->model.faces, &new, false)
		// Moves instance's pool index in the parent mesh.
		|| dynarray_push(&parent->vertices, &face_index, false)
		// Moves used mtl to to used materials pool
		|| dynarray_push(&env->model.used_mtls, used_mtl(), false))
		return (-1);
	// Negative / pool bound test.
	return (check_face_indexes(env, new));
}

int			obj_face_loader(t_env *env, char **tokens)
{
	t_mesh		*parent; // Mesh composed by the face
	uint32_t	face_index; // Index of the instance in the faces pool
	uint32_t	nb_vertexs; // Number of vertexs of the face line
	int			code;

	if (!(parent = dyacc(&env->model.meshs, (int)current_mesh))
		&& (code = create_default_mesh(env)))
		return (code);

	parent = dyacc(&env->model.meshs, (int)current_mesh);
	face_index = (uint32_t)env->model.faces.nb_cells;
	nb_vertexs = (uint32_t)ft_arrlen(tokens) - 1;

	if (env->model.faces.arr == NULL // Initialization of faces pool
		&& dynarray_init(&env->model.faces, sizeof(t_face), 256))
		return (-1);

	if (env->model.used_mtls.arr == NULL // Initialization of faces pool
		&& dynarray_init(&env->model.used_mtls, sizeof(uint32_t), 16))
		return (-1);

	if (nb_vertexs == 3) // If the face is a polygon
		return (load_face(env, tokens, parent, face_index));
	else if (nb_vertexs == 4) // Transforms quad faces to polygons, and moves them into the faces pool
		return (split_quad(env, parent, face_index, tokens));
	// If this kind of face is not handled
	return (-1);
}
