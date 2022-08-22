#include "../../includes/main.h"


// Constant array of strings used to store obj format line identifiers.
static const char	*obj_lines_ids[OBJ_MAX] = {	[OBJ_COMMENT] = "#",
													[OBJ_MTLLIB] = "mtllib",
													[OBJ_OBJECT_NAME] = "o",
													[OBJ_VERTEX] = "v",
													[OBJ_VERTEX_TEXTURE] = "vt",
													[OBJ_USEMTL] = "usemtl",
													[OBJ_FACE] = "f",
													[OBJ_SMOOTH_SHADING] = "s"
};

// Functions prototypes are here to allow the function pointer array declaration below.
static int	obj_vertex_loader(t_env *env, char **tokens);
static int	obj_vertex_texture_loader(t_env *env, char **tokens);
static int	obj_object_name_loader(t_env *env, char **tokens);
static int	obj_usemtl_loader(t_env *env, char **tokens);

// Function pointer array used to bind a function to each line identifier.
static int	(*obj_loading_fts[OBJ_MAX])(t_env *, char **) = {
													[OBJ_COMMENT] = NULL, // NULL-set members are not handled
													[OBJ_MTLLIB] = obj_mtllib_loader,
													[OBJ_OBJECT_NAME] = obj_object_name_loader,
													[OBJ_VERTEX] = obj_vertex_loader,
													[OBJ_VERTEX_TEXTURE] = obj_vertex_texture_loader,
													[OBJ_USEMTL] = obj_usemtl_loader,
													[OBJ_FACE] = obj_face_loader,
													[OBJ_SMOOTH_SHADING] = NULL
};

////////////////////////////// Loading Functions //////////////////////////////

static int	obj_object_name_loader(t_env *env, char **tokens)
{
	t_dynarray	*meshs; // Pointer used for syntaxical contraction
	t_mesh		new; // Newly created mesh

	ft_memset(&new, 0, sizeof(t_mesh));
	new.center = (vec3){0.0f, 0.0f, 0.0f, 0.0f};
	if (ft_arrlen((void **)tokens) != 2) // Format check
		return (-1);

	if (!(new.name = ft_strdup(tokens[1])) // Copies mesh's name
		|| dynarray_init(&new.vertices, sizeof(uint32_t), 256)) // Initializes faces array in the new mesh object
		return (-1);

	meshs = &env->scene.meshs;
	if ((meshs->arr == NULL && dynarray_init(meshs, sizeof(t_mesh), 1)) // Initializes meshes pool
		|| dynarray_push(meshs, &new, false)) // Moves the newly created mesh into the meshs pool
		return (-1);

	current_mesh = meshs->nb_cells - 1; // Updates current mesh affectation for vertexs and faces

	return (0);
}

static int	obj_vertex_loader(t_env *env, char **tokens)
{
	vec3	new; // New vertex object

	ft_memset(&new, 0, sizeof(vec3));
	if (ft_arrlen((void **)tokens) != 4) // Check format
		return (-1);

	if (env->scene.vertexs.arr == NULL // Initialization of vertexs pool
		&& dynarray_init(&env->scene.vertexs, sizeof(vec3), 256))
		return (-1);

	// Reads the three float components of the vertex
	new.x = (float)atof(tokens[1]);
	new.y = (float)atof(tokens[2]);
	new.z = (float)atof(tokens[3]);

	// Moves the newly created vertex into the vertexs pool
	if (dynarray_push(&env->scene.vertexs, &new, false))
		return (-1);

	return (0);
}

static int	obj_vertex_texture_loader(t_env *env, char **tokens)
{
	t_vt	new;

	ft_memset(&new, 0, sizeof(t_vt));
	if (ft_arrlen((void **)tokens) != 3) // Check format
		return (-1);

	if (env->scene.vertexs_txt.arr == NULL // Initialization of vertexs pool
		&& dynarray_init(&env->scene.vertexs_txt, sizeof(t_vt), 256))
		return (-1);

	new.u = (float)atof(tokens[1]);
	new.v = (float)atof(tokens[2]);

	// Moves the newly created vertex into the vertexs pool
	if (dynarray_push(&env->scene.vertexs_txt, &new, false))
		return (-1);

	return (0);
}

static int	obj_usemtl_loader(t_env *env, char **tokens)
{
	t_mtl	*mtl; // Pointer used to iterate through materials
	bool	found = false; // Triggers an error if the name given to usemtl is not found in materials pool

	if (ft_arrlen((void **)tokens) != 2) // Syntax check
		return (-1);

	for (int i = 0; i < env->scene.mtls.nb_cells; i++) // Iterates through mtls pool
	{
		mtl = dyacc(&env->scene.mtls, i); // Material pointer assignment
		if (ft_strcmp(mtl->name, tokens[1]) == 0) // Comparison with mtl name
		{
			found = true;
			*used_mtl() = (uint32_t)i; // Update of currently used mtl
			break;
		}
	}

	if (!found)
		return (-1);

	return (0);
}

static void	set_mesh_origin(t_env *env)
{
	t_mesh	*m;
	vec3	*v;
	vec3	acc = {0.0f, 0.0f, 0.0f, 0.0f};

	m = dyacc(&env->scene.meshs, 0);
	for (int i = 0; i < env->scene.vertexs.nb_cells; i++)
	{
		v = dyacc(&env->scene.vertexs, i);
		acc = vec_add(acc, *v);
	}
	m->center = vec_fdiv(acc, env->scene.vertexs.nb_cells);

	for (int i = 0; i < env->scene.vertexs.nb_cells; i++)
	{
		v = dyacc(&env->scene.vertexs, i);
		*v = vec_add(*v, vec_fmult(m->center, -1.0f));
	}
}

///////////////////////////////////////////////////////////////////////////////

static int	obj_loader(t_env *env, char *line)
{
	char				**tokens;
	unsigned char		code;

	// Split the line in tokens by whitespaces.
	if (!(tokens = ft_strsplit(line, "\b\t\v\f\r ")))
		return (-1);

	// Identifies line type and lauches the corresponding loader.
	for (unsigned int i = 0; i < OBJ_MAX; i++)
		if (ft_strcmp(tokens[0], obj_lines_ids[i]) == 0)
		{
			// If this line indentifier is handled
			if (obj_loading_fts[i])
			{
				// Then launch the corresponding function
				code = obj_loading_fts[i](env, tokens);
				 ft_arrfree((void **)tokens);
				return (code);
			}
			 ft_arrfree((void **)tokens);
			return (0);
		}
	// Free tokens strings array
	 ft_arrfree((void **)tokens);
	return (-1);
}

int			create_default_mesh(t_env *env)
{
	t_mesh	m; // New default mesh

	// Initializes mesh with default values
	m.center = (vec3){0.0f, 0.0f, 0.0f, 0.0f};
	if (dynarray_init(&env->scene.meshs, sizeof(t_mesh), 1)
		|| !(m.name = ft_strdup("default"))
		|| dynarray_init(&m.vertices, sizeof(uint32_t), 256))
		return (-1);

	// Adds the enterity of faces indexes to the mesh faces pool
	for (uint32_t i = 0; i < (uint32_t)env->scene.vertexs.nb_cells; i++)
		if (dynarray_push(&env->scene.vertexs, &i, false))
			return (-1);

	// Moves default mesh in meshs pool
	if (dynarray_push(&env->scene.meshs, &m, false))
		return (-1);

	// Updates current mesh index value
	current_mesh = env->scene.meshs.nb_cells - 1;

	return (0);
}

void		print_used_mtls(t_env *env)
{
	uint32_t	*n;

	for (int i = 0; i < env->scene.used_mtls.nb_cells; i++)
	{
		n = dyacc(&env->scene.used_mtls, i);
		printf("%d\n", *n);
	}
}

static int	gen_data_stride(t_env *env)
{
	t_dynarray	data; // New data stride array
	uint32_t	*f; // Pointers used to transfer data
	uint32_t	used;
	vec3		*v;
	t_vt		*vt;
	t_mtl		*m;
	t_stride	s; // New element

	if (dynarray_init(&data, sizeof(t_stride), env->scene.vertexs.nb_cells))
		return (-1);

	// Iterate through faces array
	for (int i = 0; i < env->scene.used_mtls.nb_cells; i++)
	{
		f = dyacc(&env->scene.faces, i); // Get face pointer
		// Get a pointer on the mtl used by the face

		used = *(uint32_t*)dyacc(&env->scene.used_mtls, i);
		if (used > (uint32_t)env->scene.mtls.nb_cells)
			used = 0;

		m = dyacc(&env->scene.mtls, (int)used);
		// Create 3 strides for each faces and push them into the data array
		for (unsigned int j = 0; j < 3; j++)
		{
			v = dyacc(&env->scene.vertexs, (int)f[j]);
			vt = dyacc(&env->scene.vertexs_txt, (int)f[j + 3]);
			s.v = *v;
			s.c = m  == NULL ? DEFAULT_COLOR : m->color;
			s.t = vt == NULL ? (t_vt){0.0f, 0.0f} : *vt;
			if (dynarray_push(&data, &s, false))
				return (-1);
		}
	}

	// Replace vertexs array with data
	dynarray_free(&env->scene.vertexs);
	env->scene.vertexs = data;

	printf("%d polygones\n", env->scene.faces.nb_cells);
	if (DISPLAY_DATA)
	{
		printf("%d vertexs\n", env->scene.vertexs.nb_cells);
		t_stride	*st;
		for (int i = 0; (st = dyacc(&env->scene.vertexs, i)) ; i++)
		{
			printf("vec : %f %f %f %f | color : %f %f %f %f | vec txt : %f %f\n",
				(double)st->v.x, (double)st->v.y, (double)st->v.z, (double)st->v.w, 
				(double)st->c.r, (double)st->c.g, (double)st->c.b, (double)st->c.a,
				(double)st->t.u, (double)st->t.v);
		}
	}
	return (0);
}

int			load_obj_file(t_env *env, char *path)
{
	char			**lines;
	unsigned char	code;

	*used_mtl() = UINT_MAX;
	current_mesh = INT_MAX;
	// Maps the .obj file in memory, then splits it into lines to parse it easier.
	if ((code = readlines(path, &lines)) != 0)
		return (code);

	// Iterate through lines to load obj data.
	for (unsigned int i = 0; lines[i]; i++)
		if ((code = obj_loader(env, lines[i])) != 0)
		{
			 ft_arrfree((void **)lines);
			return (code);
		}

	// Creation of a default mesh to contain vertices and faces if not declared yet.
	if (env->scene.meshs.arr == NULL && (code = create_default_mesh(env)) != 0)
	{
		 ft_arrfree((void **)lines);
		return (code);
	}
	 ft_arrfree((void **)lines);

	// Normalize vertices for OpenGL display (i.e components between -1.0 and 1.0)
	normalize_vertexs(env);

	// Place the origin of the mesh on its center by averaging its vertexs
	set_mesh_origin(env);

	return (gen_data_stride(env));
}
