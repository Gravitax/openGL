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
# include "../libs/libft/libft.h"
# include "../libs/lib_vec/lib_vec.h"

# define GLFW_INCLUDE_NONE

# define _WIDTH	 	1400
# define _HEIGHT	800
# define _LENGTH	_WIDTH * _HEIGHT


enum			e_modes
{
	MODE_COLOR,
	MODE_TEXTURE,
	MODE_LIGHT_COLOR,
	MODE_LIGHT_TEXTURE,
	MODE_MAX
};

enum			e_textures
{
	TEXTURE_DS,
	TEXTURE_NYAN,
	TEXTURE_MAX
};

enum			e_light
{
	LIGHT_POSITION,
	LIGHT_DIRECTION,
	LIGHT_COLOR,
	LIGHT_AMBIENT,
	LIGHT_DIFFUSE,
	LIGHT_SPECULAR,
	LIGHT_MAX
};

enum			e_actions
{
	ACTION_QUIT,
	ACTION_FULLSCREEN,
	ACTION_MINIFY,
	ACTION_MODE,
	ACTION_FORWARD,
	ACTION_BACKWARD,
	ACTION_RIGHT,
	ACTION_LEFT,
	ACTION_UP,
	ACTION_DOWN,
	ACTION_MAX
};

typedef struct	s_color
{
	float	r, g, b, a;
}				t_color;

typedef struct	s_texture
{
	float	u, v;
}				t_texture;

typedef struct	s_vertice
{
	vec3		pos;
	t_color		col;
	t_texture	tex;
	vec3		nor;
}				t_vertice;

typedef struct	s_mesh
{
	t_dynarray		vertices;
	unsigned int	texture;
	GLuint			ebo, vao, vbo;
}				t_mesh;

typedef struct	s_image
{
	unsigned int	w, h;
	unsigned char	*ptr;
}				t_image;

typedef float	mat4[16];

typedef struct	s_light
{
	vec3	pos, dir, color;
	vec3	ambient, diffuse, specular;
}				t_light;

typedef struct	s_camera
{
	mat4		model, view, projection;
	float		pitch, yaw;
	float		fov, near, far, ratio;
	vec3		pos, yaxis, zaxis;
	float		speed, tspeed;
	bool		ground_fixed;
}				t_camera;

typedef struct	s_mouse
{
	vec3	pos;
	bool	mounted;
	float	sensitivity;

}				t_mouse;

typedef struct	s_window
{
	bool			fullscreen;
	unsigned int	w, h;
	GLFWwindow		*ptr;
}				t_window;

typedef struct	s_uniform
{
	GLint	texture, campos, mode;
	GLint	model, view, projection;
	GLint	light[LIGHT_MAX];
}				t_uniform;

typedef struct	s_gltools
{
	GLuint			shader_program;
	GLuint			shader_vertex, shader_fragment;
	GLuint			ebo, vao, vbo;
	GLuint			textures[TEXTURE_MAX];
	const GLchar	*shader_vertex_text, *shader_fragment_text;
	t_window		window;
	t_uniform		uniform;
}				t_gltools;

typedef struct	s_fps
{
	unsigned int	frames, value;
	double			time, current_seconds, elapsed_seconds;
}				t_fps;

typedef struct	s_env
{
	char			mode;
	bool			actions[ACTION_MAX];
	void			(*events[ACTION_MAX])();
	t_fps			fps;
	t_gltools		gl;
	t_camera		camera;
	t_light			light;
	t_mouse		 	mouse;
	t_image			images[TEXTURE_MAX];
	t_dynarray		mesh;
}				t_env;

// CORE
void			events_init(t_env *env);
void			events_keyboard(t_env *env);
void			events_mouse(t_env *env, float xpos, float ypos);
void			camera(t_env *env);
int				render(t_env *env);
void			scop_exit();
int	 			scop_init(t_env *env);

// GLFW
int	 			glfw_init(t_env *env);
// callbacks
void			cb_cursor_position(GLFWwindow *window, double xpos, double ypos);
void			cb_error(int error, const char *description);
void			cb_framebuffer_size(GLFWwindow *window, int width, int height);
void			cb_key(GLFWwindow *window, int key, int scancode, int action, int mods);
void			cb_scroll(GLFWwindow *window, double xoffset, double yoffset);
void			cb_window_focus(GLFWwindow *window, int focused);

// GL
int	 			gl_init(t_env *env);
void			gl_textures(t_env *env);

// UTILS
// matrices
void			mat4_multiply(mat4 a, mat4 b);
vec3			mat4_x_vec3(mat4 m, vec3 v);

void			mat4_xrotation(mat4 m, float x);
void			mat4_yrotation(mat4 m, float y);
void			mat4_zrotation(mat4 m, float z);
void			mat4_rotate(mat4 m, float x, float y, float z);

void			mat4_identity(mat4 m);
void			mat4_inverse(mat4 m);
void			mat4_print(mat4 m);
void			mat4_translate(mat4 m, float x, float y, float z);

void			mat4_projection(mat4 m, float fov, float near, float far, float ratio);
void			mat4_lookat(mat4 m, vec3 from, vec3 to, vec3 world_up);
// bmp
unsigned char	*load_bmp(char const *pathname, unsigned int *width, unsigned int *height);
// singletons
t_env			*st_env(t_env *env, bool unsave);
// tools
void			fps(t_fps *fps, bool print);
void			shaders(t_gltools *gl);

#endif
