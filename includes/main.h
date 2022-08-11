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


enum			e_textures
{
	TEXTURE_DS,
	TEXTURE_NYAN,
	TEXTURES_MAX
};

typedef struct  s_color
{
    float   r, g, b, a;
}               t_color;

typedef struct  s_texture
{
    float   u, v;
}               t_texture;

typedef struct	s_vertice
{
    t_vec3d		pos;
    t_color     col;
    t_texture   tex;
}               t_vertice;

typedef struct	s_image
{
	unsigned int    w, h;
	unsigned char	*ptr;
}				t_image;

typedef struct	s_camera
{
	float		rot_x[4][4], rot_y[4][4], rot_z[4][4], rot[4][4];
	float		model[4][4], view[4][4], proj[4][4];
	float		pitch, roll, yaw;
	float		aspect_ratio, far, near, delta;
	float		fovd, fovr;
	t_vec3d		pos, target, up;
}				t_camera;

typedef struct  s_window
{
    unsigned int	w;
	unsigned int	h;
    GLFWwindow      *ptr;
}               t_window;


typedef struct  s_gltools
{
    GLuint          shader_program;
    GLuint          shader_vertex;
    GLuint          shader_fragment;
    GLuint          ebo;
    GLuint          vao;
    GLuint          vbo;
    GLuint          textures[TEXTURES_MAX];
    const GLchar    *shader_vertex_text;
    const GLchar    *shader_fragment_text;
    t_window        window;
}               t_gltools;


typedef struct	s_env
{
	unsigned int	texture;
    unsigned int    frames;
    unsigned int    fps;
    double          time;
    t_gltools       gl;
	t_camera		camera;
    t_dynarray      vertices;
    t_image			images[TEXTURES_MAX];
}				t_env;

// CORE
void			init_camera(t_env *env);
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
int				gl_textures(t_env *env);

// UTILS
// matrix
void			matrix_mult_matrix(float m1[4][4], float m2[4][4], float ret[4][4]);
t_vec3d			matrix_mult_vec(float m[4][4], t_vec3d i);

void			matrix_xrotation(float m[4][4], float theta);
void			matrix_yrotation(float m[4][4], float theta);
void			matrix_zrotation(float m[4][4], float theta);

void			matrix_identity(float m[4][4]);
void			matrix_inverse(float m[4][4], float r[4][4]);
void			matrix_flattener(float m[4][4], float flat[16]);
void			matrix_translation(float m[4][4], t_vec3d v);

void			matrix_pointat(float m[4][4], t_vec3d pos, t_vec3d target, t_vec3d up);
void			matrix_view(t_camera *camera);

// bmp
unsigned char	*load_bmp(char const *pathname, unsigned int *width, unsigned int *height);
// singletons
t_env			*st_env(t_env *env, bool unsave);

#endif
