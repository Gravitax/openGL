#include "main.h"


void    	cb_error(int error, const char *description)
{
    fprintf(stderr, "Error: (%d): %s\n", error, description);
    scop_exit();
}

static void	camera_translation(t_env *env, int key)
{
	t_camera	*camera;
	float		camera_speed;

	camera = &env->camera;
	camera_speed = camera->speed * env->fps.elapsed_seconds;
	switch (key)
	{
		case GLFW_KEY_W:
			printf("key Z pressed\n");
			camera->pos = vec_add(camera->pos, vec_fmult(camera->target, camera_speed));
			break ;
        case GLFW_KEY_S:
			printf("key S pressed\n");
			camera->pos = vec_sub(camera->pos, vec_fmult(camera->target, camera_speed));
			break ;
		case GLFW_KEY_A:
            printf("key Q pressed\n");
			camera->pos = vec_add(camera->pos, vec_normalize(vec_fmult(vec_cross(camera->target, camera->up), camera_speed)));
            break ;
		case GLFW_KEY_D:
            printf("key D pressed\n");
			camera->pos = vec_sub(camera->pos, vec_normalize(vec_fmult(vec_cross(camera->target, camera->up), camera_speed)));
            break ;
	}
	printf("%f %f %f\n", camera->pos.x, camera->pos.y, camera->pos.z);
}

static void	camera_rotation(t_env *env, int key)
{
	t_camera	*camera;
	float		camera_speed;

	camera = &env->camera;
	camera_speed = camera->speed * 10 * env->fps.elapsed_seconds;
	switch (key)
	{
		case GLFW_KEY_Q:
			printf("key A pressed\n");
			camera->yaw += camera_speed;
            break ;
        case GLFW_KEY_E:
            printf("key E pressed\n");
			camera->yaw -= camera_speed;
            break ;
	}
	// if (camera->yaw > 89)
	// 	camera->yaw = 89;
	// if (camera->yaw < -89)
	// 	camera->yaw = -89;
}
 
void    	cb_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
		t_env		*env;

		if (!(env = st_env(NULL, false)))
			return ;
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break ;
            case GLFW_KEY_I:
                glfwIconifyWindow(window);
                break ;
            case GLFW_KEY_M:
                glfwGetWindowAttrib(window, GLFW_MAXIMIZED)
                    ? glfwRestoreWindow(window) : glfwMaximizeWindow(window);
                break ;
            case GLFW_KEY_R:
                glfwRestoreWindow(window);
                break ;
            case GLFW_KEY_F:
			    printf("key F pressed\n");
				env->texture = env->texture + 1 >= TEXTURES_MAX ? 0 : env->texture + 1;
				break ;
            case GLFW_KEY_W: case GLFW_KEY_S: case GLFW_KEY_A: case GLFW_KEY_D:
				camera_translation(env, key);
				break ;
            case GLFW_KEY_Q: case GLFW_KEY_E:
				camera_rotation(env, key);
				break ;
            default:
                printf("key: %d\n", key);
        }
    }
}

void    	cb_cursor_position(GLFWwindow *window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
}

void    	cb_window_maximize(GLFWwindow *window, int maximized)
{
    if (maximized)
    {
        // The window was maximized
        printf("The window was maximized\n");
    }
    else
    {
        // The window was restored
        printf("The window was restored\n");
    }
}

void    	cb_window_focus(GLFWwindow *window, int focused)
{
    if (focused)
    {
        // The window gained input focus
        printf("The window gained input focus\n");
    }
    else
    {
        // The window lost input focus
        printf("The window lost input focus\n");
    }
}

void    	cb_scroll(GLFWwindow *window, double xoffset, double yoffset)
{
    printf("offset_x: %f, offset_y: %f\n", xoffset, yoffset);
}

void		cb_framebuffer_size(GLFWwindow *window, int width, int height)
{
	t_env	*env;

	env = st_env(NULL, false);
	if (env == NULL)
		return ;
    glViewport(0, 0, width, height);
	env->gl.window.w = width;
	env->gl.window.h = height;
}
