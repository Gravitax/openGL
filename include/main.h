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
# include "bmp.h"

# define GLFW_INCLUDE_NONE

# define _WIDTH     640
# define _HEIGHT    480
# define _LENGTH    _WIDTH * _HEIGHT


typedef struct  s_vec3
{
    float   x, y, z, w;
}               t_vec3;

typedef struct  s_color
{
    float   r, g, b, a;
}               t_color;

typedef struct  s_texture
{
    float   x, y;
}               t_texture;

typedef struct	s_vertices
{
    t_vec3      pos;
    t_color     col;
    t_texture   tex;
}               t_vertices;

typedef struct	s_env
{
    GLFWwindow      *window;
    GLuint          ebo;
    GLuint          vao;
    GLuint          vbo;
    GLuint          shader_program;
    GLuint          shader_vertex;
    GLuint          shader_fragment;
    GLuint          tex;
    double          time;
    int             frames;
    int             fps;
    t_dynarray      vertices;
    unsigned char   *img;
    int             img_w;
    int             img_h;
    const GLchar    *shader_vertex_text;
    const GLchar    *shader_fragment_text;
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

void    gl_shaders(t_env *env);

int     env_init(t_env *env);

void    scop_exit(t_env *env);

t_env   *singleton(t_env *env);

#endif
