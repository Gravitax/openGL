#ifndef MAIN_H
# define MAIN_H

// OpenGL Libs
# include "glad.h"
# include <GLFW/glfw3.h>

# include <errno.h>
# include <string.h>

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

// Homemade libs
# include "../libs/libft/libft.h"
# include "../libs/lib_vec/lib_vec.h"
# include "./parser.h"

# define GLFW_INCLUDE_NONE

# define _WIDTH	 	1400
# define _HEIGHT	800
# define _LENGTH	_WIDTH * _HEIGHT

# define DEFAULT_COLOR (t_color){ 1.0f, 0.0f, 0.0f, 1.0f }


enum			e_light
{
	LIGHT_ACTIVE,
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
	// UI
	ACTION_UI_QUIT,
	ACTION_UI_FULLSCREEN,
	ACTION_UI_LIGHT,
	ACTION_UI_MINIFY,
	ACTION_UI_MODE,
	ACTION_UI_LSHIFT,
	ACTION_UI_RSHIFT,
	// CAMERA
	ACTION_CAM_FORWARD,
	ACTION_CAM_BACKWARD,
	ACTION_CAM_RIGHT,
	ACTION_CAM_LEFT,
	ACTION_CAM_UP,
	ACTION_CAM_DOWN,
	// MODEL
	ACTION_MODEL_FORWARD,
	ACTION_MODEL_BACKWARD,
	ACTION_MODEL_RIGHT,
	ACTION_MODEL_LEFT,
	ACTION_MODEL_UP,
	ACTION_MODEL_DOWN,
	ACTION_MODEL_PROTX,
	ACTION_MODEL_NROTX,
	ACTION_MODEL_PROTY,
	ACTION_MODEL_NROTY,
	ACTION_MODEL_PROTZ,
	ACTION_MODEL_NROTZ,
	ACTION_MAX
};

typedef float	mat4[16];

typedef struct	s_color
{
	float	r, g, b, a;
}				t_color;

typedef struct	s_textcoord
{
	float	u, v;
}				t_vt;

typedef struct	s_stride
{
	vec3		v;
	t_color		c;
	t_vt		t;
}				t_stride;

typedef struct	s_mesh
{
	t_dynarray		vertices;
	t_dynarray		faces;
	vec3			center;
	unsigned int	texture;
	GLuint			ebo, vao, vbo;
	char			*name;
}				t_mesh;

// ==========================================

typedef struct	s_image
{
	unsigned int	w, h;
	unsigned char	*ptr;
}				t_image;

typedef	struct	s_material
{
	t_color		color;
	char		*name;
}				t_mtl;

typedef	struct	s_face
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	va;
	uint32_t	vb;
	uint32_t	vc;
}				t_face;

// ==========================================

typedef struct	s_model
{
	mat4		model;
	vec3		trans, rot;
	vec3		center;
	float		scale;
	char		obj_path[256];
	t_image		texture;

	t_dynarray	meshs;
	t_dynarray	vertexs;
	t_dynarray	vertexs_txt;
	t_dynarray	faces;
	t_dynarray	used_mtls;
	t_dynarray	mtls;
}				t_model;

// ==========================================

typedef struct	s_mouse
{
	vec3	pos;
	float	sensitivity;

}				t_mouse;

typedef struct	s_camera
{
	mat4		view, projection;
	float		pitch, yaw;
	float		fov, near, far, ratio;
	vec3		pos, yaxis, zaxis;
	float		speed, tspeed;
	bool		ground_fixed;
}				t_camera;

// ==========================================

typedef struct	s_window
{
	bool			fullscreen;
	unsigned int	w, h;
	GLFWwindow		*ptr;
}				t_window;

typedef struct	s_uniform
{
	GLint	texture, campos, progress;
	GLint	model, view, projection;
	GLint	light[LIGHT_MAX];
}				t_uniform;

typedef struct	s_gltools
{
	GLuint			shader_program;
	GLuint			shader_vertex, shader_geometry, shader_fragment;
	GLuint			ebo, vao, vbo;
	GLuint			texture;
	const GLchar	*shader_vertex_text, *shader_fragment_text;
	t_window		window;
	t_uniform		uniform;
}				t_gltools;

// ==========================================

typedef struct	s_fps
{
	unsigned int	frames, value;
	double			time, current_seconds, elapsed_seconds;
}				t_fps;

typedef struct	s_animation
{
	float	progress, step;
	bool	active;
}				t_animation;

typedef struct	s_light
{
	bool	active;
	vec3	pos, dir, color;
	vec3	ambient, diffuse, specular;
}				t_light;

// ==========================================

typedef struct	s_env
{
	bool			actions[ACTION_MAX];
	void			(*events[ACTION_MAX])();
	t_fps			fps;
	t_gltools		gl;
	t_camera		camera;
	t_light			light;
	t_mouse		 	mouse;
	t_model			model;
	t_animation		animation;
}				t_env;

// CORE
void			events_camera(t_env *env);
void			events_keyboard(t_env *env);
void			events_model(t_env *env);
void			events_mouse(t_env *env, float xpos, float ypos);
void			events(t_env *env);
void			camera(t_env *env);
int				model(t_env *env);
int				render(t_env *env);
void			scop_exit();
int	 			scop_init(t_env *env);

// GL
int	 			gl_init(t_env *env);
void			gl_textures(t_env *env);

// GLFW
int	 			glfw_init(t_env *env);
// callbacks
void			cb_cursor_position(GLFWwindow *window, double xpos, double ypos);
void			cb_error(int error, const char *description);
void			cb_framebuffer_size(GLFWwindow *window, int width, int height);
void			cb_key(GLFWwindow *window, int key, int scancode, int action, int mods);
void			cb_scroll(GLFWwindow *window, double xoffset, double yoffset);
void			cb_window_focus(GLFWwindow *window, int focused);

// PARSER
int				load_obj_file(t_env *env, char *path);
int				readlines(char *path, char ***lines);
int				load_settings(t_env *env);
int				obj_mtllib_loader(t_env *env, char **tokens);
void			normalize_vertexs(t_env *env);

int				obj_face_loader(t_env *env, char **tokens);
int				create_default_mesh(t_env *env);

int				mtl_newmtl_loader(t_env *env, char **tokens);
int				mtl_diffuse_color_loader(t_env *env, char **tokens);
int				mtl_alpha_component_loader(t_env *env, char **tokens);
int				mtl_texture_image_loader(t_env *env, char **tokens);

// UTILS
// matrices
void			mat4_multiply(mat4 a, mat4 b);
vec3			mat4_x_vec3(mat4 m, vec3 v);

void			mat4_xrotation(mat4 m, float x);
void			mat4_yrotation(mat4 m, float y);
void			mat4_zrotation(mat4 m, float z);
void			mat4_rotate(mat4 m, float x, float y, float z);

void			mat4_identity(mat4 m);
void			mat4_scale(mat4 m, float scale);
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
