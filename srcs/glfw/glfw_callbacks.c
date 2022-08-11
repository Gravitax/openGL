#include "main.h"


void    cb_error(int error, const char *description)
{
    fprintf(stderr, "Error: (%d): %s\n", error, description);
    scop_exit();
}

static void	camera_position(t_camera *camera, float x, float y, float z)
{
	camera->pos.x += x;
	camera->pos.y += y;
	camera->pos.z += z;
}
 
void    cb_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
		t_env	*env;

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
            case GLFW_KEY_W:
			    printf("key Z pressed\n");
				camera_position(&env->camera, 0, 0, 0.1f);
				break ;
            case GLFW_KEY_S:
				printf("key S pressed\n");
				camera_position(&env->camera, 0, 0, -0.1f);
				break ;
			 case GLFW_KEY_A:
                printf("key Q pressed\n");
				camera_position(&env->camera, -0.1f, 0, 0);
                break ;
			 case GLFW_KEY_D:
                printf("key D pressed\n");
				camera_position(&env->camera, 0.1f, 0, 0);
                break ;
            case GLFW_KEY_Q:
                printf("key A pressed\n");
				env->camera.yaw += 2.f;
                break ;
            case GLFW_KEY_E:
                printf("key E pressed\n");
				env->camera.yaw -= 2.f;
                break ;
            default:
                printf("key: %d\n", key);
        }
    }
}

void    cb_cursor_position(GLFWwindow *window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
}

void    cb_window_maximize(GLFWwindow *window, int maximized)
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

void    cb_window_focus(GLFWwindow *window, int focused)
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

void    cb_scroll(GLFWwindow *window, double xoffset, double yoffset)
{
    printf("offset_x: %f, offset_y: %f\n", xoffset, yoffset);
}

void	cb_framebuffer_size(GLFWwindow *window, int width, int height)
{
	t_env	*env;

	env = st_env(NULL, false);
	if (env == NULL)
		return ;
    glViewport(0, 0, width, height);
	env->gl.window.w = width;
	env->gl.window.h = height;
}
