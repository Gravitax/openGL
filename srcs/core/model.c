#include "../../includes/main.h"


static void	cube(t_dynarray *vertices, float x, float y, float z)
{
	//										x			y		z		w		r	g		b	a		u	v		nx	ny		nz
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.4f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.2f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 0.8f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.0f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.0f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.0f, 0.0f, 0.8f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.0f, 0.0f, 0.6f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.0f, 0.0f, 0.4f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 0.0f, 0.2f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
}

static void	set_mesh_center(t_mesh *mesh)
{
	int			i;
	vec3		sum = (vec3){};
	t_vertice	*vertices;

	i = -1;
	while (++i < mesh->vertices.nb_cells) {
		vertices = dyacc(&mesh->vertices, i);
		if (vertices == NULL)
			continue ;
		sum = vec_add(sum, vertices->pos);
	}
	mesh->center = vec_fdiv(sum, i);
	i = -1;
	while (++i < mesh->vertices.nb_cells) {
		vertices = dyacc(&mesh->vertices, i);
		if (vertices == NULL)
			continue ;
		vertices->pos = vec_add(vertices->pos, vec_fmult(mesh->center, -1));
		vertices->pos.w = 1;
	}
}

int			model(t_env *env)
{
	int		i, mesh_max;
	t_mesh	*mesh;

	mesh_max = 1;
	env->model.center = (vec3){};
	if (dynarray_init(&env->model.mesh, sizeof(t_mesh), mesh_max) < 0)
		return (-1);
	i = -1;
	while (++i < mesh_max) {
		mesh = dyacc(&env->model.mesh, i);
		if (mesh == NULL)
			continue ;
		if (dynarray_init(&mesh->vertices, sizeof(t_vertice), 36) < 0)
			return (-1);
		cube(&mesh->vertices, 0, i * 4, i * 4);
		set_mesh_center(mesh);
		env->model.center = vec_add(env->model.center, mesh->center);
		mesh->texture = i % 2 ? TEXTURE_NYAN : TEXTURE_DS;
		if (dynarray_push(&env->model.mesh, mesh, true) < 0)
			return (-1);
	}
	env->model.center = (vec3){ env->model.center.x / i, env->model.center.y / i, env->model.center.z / i };
	env->model.scale = 1;
	return (0);
}
