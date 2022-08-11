#include "main.h"


static void	matrix_projection(t_camera *camera)
{
	camera->proj[0][0] = camera->aspect_ratio * camera->fovr;
	camera->proj[1][1] = camera->fovr;
	camera->proj[2][2] = camera->far / camera->delta;
	camera->proj[3][2] = (-camera->far * camera->near) / camera->delta;
	camera->proj[2][3] = 1;
	camera->proj[3][3] = 0;
}

static void	init_matrices(t_camera *camera)
{
	int	i = -1;

	while (++i < 4) {
		ft_memset(&camera->rot_x[i], 0, sizeof(float) * 4);
		ft_memset(&camera->rot_y[i], 0, sizeof(float) * 4);
		ft_memset(&camera->rot_z[i], 0, sizeof(float) * 4);
		ft_memset(&camera->rot[i], 0, sizeof(float) * 4);
		ft_memset(&camera->model[i], 0, sizeof(float) * 4);
		ft_memset(&camera->view[i], 0, sizeof(float) * 4);
		ft_memset(&camera->proj[i], 0, sizeof(float) * 4);
		camera->rot_x[i][i] = 1;
		camera->rot_y[i][i] = 1;
		camera->rot_z[i][i] = 1;
		camera->model[i][i] = 1;
		camera->view[i][i] = 1;
		camera->proj[i][i] = 1;
	}
	matrix_projection(camera);
}

void		init_camera(t_env *env)
{
	t_camera *camera = &env->camera;

	camera->aspect_ratio = (float)env->gl.window.h / (float)env->gl.window.w;

	// Far and near plane definitions
	camera->near = 0.01f;
	camera->far = 100000.0f;
	camera->delta = camera->far - camera->near;

	// FOV
	camera->fovd = 90.0f;
	camera->fovr = 1.0f / tanf(camera->fovd * 0.5f / 180.0f * 3.14159f);

	// Camera's starting position and orientation
	camera->pos = (t_vec3d){ 0, 0, 0, 0 };
	camera->target = (t_vec3d){ 0, 0, 1, 0 };
	camera->up = (t_vec3d){ 0, 1, 0, 0 };

	// Camera rotations
	camera->pitch = 0;
	camera->roll = 0;
	camera->yaw = 0;

	init_matrices(camera);
}
