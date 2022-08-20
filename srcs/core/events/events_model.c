#include "../../../includes/main.h"


// MODEL ==========================================

// TRANSLATION FORWARD
static void	model_forward(t_model *model)
{
	mat4_translate(model->model, 0, 0, 1);
}

// TRANSLATION BACKWARD
static void	model_backward(t_model *model)
{
	mat4_translate(model->model, 0, 0, -1);
}

// TRANSLATION RIGHT
static void	model_right(t_model *model)
{
	mat4_translate(model->model, -1, 0, 0);
}

// TRANSLATION LEFT
static void	model_left(t_model *model)
{
	mat4_translate(model->model, 1, 0, 0);
}

// TRANSLATION UP
static void	model_up(t_model *model)
{
	mat4_translate(model->model, 0, 1, 0);
}

// TRANSLATION DOWN
static void	model_down(t_model *model)
{
	mat4_translate(model->model, 0, -1, 0);
}

// POSITIVE ROTX
static void	model_protx(t_model *model)
{
	mat4	m;

	mat4_xrotation(m, 0.1f);
	mat4_multiply(model->model, m);
}

// NEGATIVE ROTX
static void	model_nrotx(t_model *model)
{
	mat4	m;

	mat4_xrotation(m, -0.1f);
	mat4_multiply(model->model, m);
}

// POSITIVE ROTY
static void	model_proty(t_model *model)
{
	mat4	m;

	mat4_yrotation(m, 0.1f);
	mat4_multiply(model->model, m);
}

// NEGATIVE ROTY
static void	model_nroty(t_model *model)
{
	mat4	m;

	mat4_yrotation(m, -0.1f);
	mat4_multiply(model->model, m);
}

// POSITIVE ROTZ
static void	model_protz(t_model *model)
{
	mat4	m;

	mat4_zrotation(m, 0.1f);
	mat4_multiply(model->model, m);
}

// NEGATIVE ROTZ
static void	model_nrotz(t_model *model)
{
	mat4	m;

	mat4_zrotation(m, -0.1f);
	mat4_multiply(model->model, m);
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
