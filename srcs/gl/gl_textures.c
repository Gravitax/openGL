#include "../../includes/main.h"


void		gl_textures(t_env *env)
{
	t_image	image;
	int		i = -1;

	glGenTextures(1, &env->gl.texture);
	while (++i < 1) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, env->gl.texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		image = env->model.texture;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.w, image.h, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
