#include "../../../includes/main.h"


// TRANSLATION FORWARD
static void	model_forward(t_model *model)
{
	model->trans.z += model->strans;
}

// TRANSLATION BACKWARD
static void	model_backward(t_model *model)
{
	model->trans.z -= model->strans;
}

// TRANSLATION RIGHT
static void	model_right(t_model *model)
{
	model->trans.x -= model->strans;
}

// TRANSLATION LEFT
static void	model_left(t_model *model)
{
	model->trans.x += model->strans;
}

// TRANSLATION UP
static void	model_up(t_model *model)
{
	model->trans.y += model->strans;
}

// TRANSLATION DOWN
static void	model_down(t_model *model)
{
	model->trans.y -= model->strans;
}

// POSITIVE ROTX
static void	model_protx(t_model *model)
{
	model->rot.x += model->srot;
}

// NEGATIVE ROTX
static void	model_nrotx(t_model *model)
{
	model->rot.x -= model->srot;
}

// POSITIVE ROTY
static void	model_proty(t_model *model)
{
	model->rot.y += model->srot;
}

// NEGATIVE ROTY
static void	model_nroty(t_model *model)
{
	model->rot.y -= model->srot;
}

// POSITIVE ROTZ
static void	model_protz(t_model *model)
{
	model->rot.z += model->srot;
}

// NEGATIVE ROTZ
static void	model_nrotz(t_model *model)
{
	model->rot.z -= model->srot;
}

void		events_model(t_env *env)
{
	// translations
	env->events[ACTION_MODEL_FORWARD] = model_forward;
	env->events[ACTION_MODEL_BACKWARD] = model_backward;
	env->events[ACTION_MODEL_RIGHT] = model_right;
	env->events[ACTION_MODEL_LEFT] = model_left;
	env->events[ACTION_MODEL_UP] = model_up;
	env->events[ACTION_MODEL_DOWN] = model_down;
	//rotations
	env->events[ACTION_MODEL_PROTX] = model_protx;
	env->events[ACTION_MODEL_NROTX] = model_nrotx;
	env->events[ACTION_MODEL_PROTY] = model_proty;
	env->events[ACTION_MODEL_NROTY] = model_nroty;
	env->events[ACTION_MODEL_PROTZ] = model_protz;
	env->events[ACTION_MODEL_NROTZ] = model_nrotz;
}
