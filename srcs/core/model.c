#include "../../includes/main.h"


static void	cube(t_dynarray *vertices, float x, float y, float z)
{
	//										x			y			z			r		g		b	a		u	v		nx	ny		nz
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 0.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 2.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 2.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }, false);
	dynarray_push(vertices, &(t_vertice){ 0.0f + x, 2.0f + y, 0.0f + z, 1.0f, 0.5f, 0.2f + y, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }, false);
}

int			model(t_env *env)
{
	unsigned int	i, mesh_max;
	t_mesh			*mesh;

	mesh_max = 2;
	if (dynarray_init(&env->model.mesh, sizeof(t_mesh), mesh_max) < 0)
		return (-1);
	for (i = 0; i < mesh_max; i++) {
		mesh = dyacc(&env->model.mesh, i);
		if (mesh == NULL)
			continue ;
		if (dynarray_init(&mesh->vertices, sizeof(t_vertice), 36) < 0)
			return (-1);
		cube(&mesh->vertices, 0, i * 4, i * 4);
		mesh->texture = i % 2 ? TEXTURE_NYAN : TEXTURE_DS;
		if (dynarray_push(&env->model.mesh, mesh, true) < 0)
			return (-1);
	}
	// Model matrix
	mat4_identity(env->model.model);
	return (0);
}
