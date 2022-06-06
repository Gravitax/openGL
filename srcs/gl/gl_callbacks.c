#include "main.h"


void    cb_error(int error, const char *description)
{
    fprintf(stderr, "Error: (%d): %s\n", error, description);
    scop_exit();
}
 
void    cb_key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
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
            case GLFW_KEY_A:
                printf("key A pressed\n");
                break ;
            case GLFW_KEY_D:
                printf("key D pressed\n");
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
	env->ww = width;
	env->wh = height;
}
