#include "../../includes/main.h"


static void	mat4_view(t_camera *camera)
{
	vec3	from, forward, up;

	from = mat4_x_vec3(camera->rot_xyz, camera->pos);
	forward = camera->target;
	up = camera->up;

	// from = camera->pos;
	// forward = mat4_x_vec3(camera->rot_xyz, camera->target);
	// up = mat4_x_vec3(camera->rot_xyz, camera->up);

	// forward.x = cosf(camera->yaw) * cosf(camera->pitch);
    // forward.y = sinf(camera->pitch);
    // forward.z = sinf(camera->yaw) * cosf(camera->pitch);

	mat4_lookat(camera->view, from, vec_add(from, forward), up);
	// mat4_inverse(camera->view);
}

static void	matrices(t_gltools *gl, t_camera *camera)
{
	mat4_view(camera);
	mat4_identity(camera->mvp);
	mat4_multiply(camera->mvp, camera->projection);
	mat4_multiply(camera->mvp, camera->view);
	mat4_multiply(camera->mvp, camera->model);
	glUniformMatrix4fv(gl->uniform.mvp, 1, GL_FALSE, camera->mvp);
}

static void	draw(t_env *env) {
	glDrawArrays(GL_TRIANGLES, 0, env->vertices.nb_cells);
}

int         render(t_env *env)
{
    if (glfwWindowShouldClose(env->gl.window.ptr))
        return (-1);

    glfw_fps(&env->fps, true);
	glfwPollEvents();
	events(env);

    glfwGetFramebufferSize(env->gl.window.ptr, (int *)&env->gl.window.w, (int *)&env->gl.window.h);
	glViewport(0, 0, (int)env->gl.window.w, (int)env->gl.window.h);

 	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int	i = -1;
	while (++i < TEXTURES_MAX) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, env->gl.textures[env->texture]);
	}

	matrices(&env->gl, &env->camera);

	// glUseProgram(env->gl.shader_program);
    // glBindVertexArray(env->gl.vao);

	draw(env);

    glfwSwapBuffers(env->gl.window.ptr);
    return (0);
}
