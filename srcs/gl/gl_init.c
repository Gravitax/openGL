#include "main.h"


static void	set_image(t_image image) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.w, image.h, 0, GL_BGR, GL_UNSIGNED_BYTE, image.img);
	glGenerateMipmap(GL_TEXTURE_2D);
}

static void gl_vobjects(t_env *env, int i)
{
    GLuint  elements[] = {
        3, 1, 0,
        2, 3, 0
    };

	// CULLING : we only draw front face in clock-wise order
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glFrontFace(GL_CW);

    // Create Vertex Array Object
    glGenVertexArrays(1, &env->vao[i]);
    glBindVertexArray(env->vao[i]);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &env->vbo[i]);
    glBindBuffer(GL_ARRAY_BUFFER, env->vbo[i]);
    glBufferData(GL_ARRAY_BUFFER,
        env->vertices[i].nb_cells * sizeof(t_vertice),
        env->vertices[i].arr, GL_STATIC_DRAW);

    // Create an Elements Buffer Object
    glGenBuffers(1, &env->ebo[i]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

int		gl_init(t_env *env)
{
	int	i = -1;

	if (gl_textures(env) < 0)
		return (-1);
	while (++i < ELEMENTS_MAX) {
		gl_vobjects(env, i);
		if (gl_shaders(env) < 0)
			return (-1);
		set_image(env->images[i]);
	}
	return (0);
}
