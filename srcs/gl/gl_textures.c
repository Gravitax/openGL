#include "main.h"


int			gl_textures(t_env *env)
{
	int	i = -1;

	while (++i) {
		glGenTextures(1, &env->textures[i]);
		glBindTexture(GL_TEXTURE_2D, env->textures[i]);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glUniform1i(glGetUniformLocation(env->shader_program, "in_texture"), 0);
	return (0);
}
