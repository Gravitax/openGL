#ifndef MAIN_H
# define MAIN_H

// OpenGL Libs
# include "glad.h"
# include <GLFW/glfw3.h>

# include <stdio.h>
# include <stdbool.h>

// Homemade libs
# include "libft.h"
# include "lib_vec.h"

# include "linmath.h"

# define GLFW_INCLUDE_NONE

# define _WIDTH     640
# define _HEIGHT    480
# define _LENGTH    _WIDTH * _HEIGHT

typedef struct	s_vertices
{
    float   x, y, z;
    float   r, g, b;
}               t_vertices;

typedef struct	s_env
{
    GLFWwindow  *window;
    GLuint      ebo;
    GLuint      vao;
    GLuint      vbo;
    GLuint      shader_program;
    GLuint      shader_vertex;
    GLuint      shader_fragment;
    double      time;
    int         frames;
    int         fps;
    t_vertices  vertices[4];
}				t_env;

// CALLBACK
void    error_callback(int error, const char *description);
void    key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void    cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void    window_maximize_callback(GLFWwindow *window, int maximized);
void    window_focus_callback(GLFWwindow *window, int focused);
void    scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void    gl_fps(t_env *env, bool print);

int     gl_init(t_env *env);

#endif
