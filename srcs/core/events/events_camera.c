#include "../../../includes/main.h"


// TRANSLATION FRONT
static void	cam_forward(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(camera->zaxis, camera->tspeed));
}

// TRANSLATION BACK
static void	cam_backward(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(camera->zaxis, camera->tspeed));
}

// TRANSLATION RIGHT
static void	cam_right(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera->tspeed));
}

// TRANSLATION LEFT
static void	cam_left(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(vec_cross(camera->zaxis, camera->yaxis), camera->tspeed));
}

// TRANSLATION UP
static void	cam_up(t_camera *camera)
{
	camera->pos = vec_add(camera->pos, vec_fmult(camera->yaxis, camera->tspeed));
}

// TRANSLATION DOWN
static void	cam_down(t_camera *camera)
{
	camera->pos = vec_sub(camera->pos, vec_fmult(camera->yaxis, camera->tspeed));
}

void		events_camera(t_env *env)
{
	env->events[ACTION_CAM_FORWARD] = cam_forward;
	env->events[ACTION_CAM_BACKWARD] = cam_backward;
	env->events[ACTION_CAM_RIGHT] = cam_right;
	env->events[ACTION_CAM_LEFT] = cam_left;
	env->events[ACTION_CAM_UP] = cam_up;
	env->events[ACTION_CAM_DOWN] = cam_down;
}
