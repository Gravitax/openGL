#ifndef MAIN_H
# define MAIN_H

// OpenGL Libs
# include "glad.h"
# include <GLFW/glfw3.h>

# include <stdio.h>
# include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


// Homemade libs
# include "libft.h"
# include "lib_vec.h"

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
	int				ww;
	int				wh;
}				t_env;

// CORE
int				render(t_env *env);
void    		scop_exit();
int     		scop_init(t_env *env);

// GLFW
void    		glfw_fps(t_env *env, bool print);
int     		glfw_init(t_env *env);
// callbacks
void    		cb_error(int error, const char *description);
void    		cb_key(GLFWwindow *window, int key, int scancode, int action, int mods);
void    		cb_cursor_position(GLFWwindow *window, double xpos, double ypos);
void    		cb_window_maximize(GLFWwindow *window, int maximized);
void    		cb_window_focus(GLFWwindow *window, int focused);
void    		cb_scroll(GLFWwindow *window, double xoffset, double yoffset);
void			cb_framebuffer_size(GLFWwindow *window, int width, int height);

// GL
int     		gl_init(t_env *env);
int				gl_shaders(t_env *env);
int				gl_textures(t_env *env);

// UTILS
unsigned char	*load_bmp(char const *pathname, int *width, int *height);
// singletons
t_env			*st_env(t_env *env, bool unsave);

#endif
