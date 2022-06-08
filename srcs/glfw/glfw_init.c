#include "main.h"


static int  glfw_create_window(GLFWwindow* *window, const char *title, bool fullscreen)
{
    GLFWmonitor         *monitor;
    const GLFWvidmode   *mode;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
    if (fullscreen)
    {
        monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
 
        *window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    }
    else
        *window = glfwCreateWindow(_WIDTH, _HEIGHT, title, NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        return (-1);
    }
    return(0);
}

static void glfw_init_callbacks(GLFWwindow* window)
{
    glfwSetKeyCallback(window, cb_key);
    // glfwSetCursorPosCallback(window, cb_cursor_position);
    // glfwSetWindowMaximizeCallback(window, cb_window_maximize);
    // glfwSetWindowFocusCallback(window, cb_window_focus);
    // glfwSetScrollCallback(window, cb_scroll);
	glfwSetFramebufferSizeCallback(window, cb_framebuffer_size);
}

int         glfw_init(t_env *env)
{
    glfwSetErrorCallback(cb_error);
	if (!glfwInit() || !GL_VERSION_2_1)
		return (-1);
    if (glfw_create_window(&env->window, "scop", false) < 0)
        return (-1);
	glfwMakeContextCurrent(env->window);
	if (!gladLoadGL())
		return (-1);
	glfwSwapInterval(1);
    glfw_init_callbacks(env->window);
    return (0);
}
