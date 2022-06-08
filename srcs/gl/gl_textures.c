#include "main.h"


static int  load_img(t_env *env)
{
	env->img = load_bmp("./ressources/images/texture.bmp", &env->img_w, &env->img_h);
    return (env->img ? 0 : -1);
}

int			gl_textures(t_env *env)
{
    glGenTextures(1, &env->tex);
    glBindTexture(GL_TEXTURE_2D, env->tex);

    glUniform1i(glGetUniformLocation(env->shader_program, "tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (load_img(env) < 0)
		return (-1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->img_w, env->img_h, 0, GL_BGR, GL_UNSIGNED_BYTE, env->img);

    // Black/white checkerboard
    // float pixels[] = {
    //     1.f, 1.f, 1.f,   0.f, 0.f, 0.f,
    //     0.f, 0.f, 0.f,   0.f, 0.f, 0.f
    // };
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);
	return (0);
}
