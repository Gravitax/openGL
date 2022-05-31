#ifndef MAIN_H
# define MAIN_H

// OpenGL Libs
# include "glad.h"
# include <GLFW/glfw3.h>

# include <stdio.h>

// Homemade libs
# include "libft.h"
# include "lib_vec.h"

# include "linmath.h"

# define GLFW_INCLUDE_NONE

# define _WIDTH 640
# define _HEIGHT 480


// CALLBACK
void    error_callback(int error, const char* description);
void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void    cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void    window_maximize_callback(GLFWwindow* window, int maximized);
void    window_focus_callback(GLFWwindow* window, int focused);
void    scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif
