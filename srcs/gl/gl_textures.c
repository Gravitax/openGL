#include "main.h"


static void	reverse_image(t_env *env)
{
	if (!env || !env->img)
		return ;
	// int				pad = sizeof(unsigned char) * 3;
	// int				start, end;
	// unsigned char	tmp1[2], tmp2[2];
	// unsigned char	t;

	// for (int i = 0, length = env->img_w * env->img_h * 3; i < length; i++) {
	// 	start = i * 3;
	// 	end = length - (i  + 1) * 3;
	// 	ft_memcpy(tmp1, env->img + start, pad);
	// 	ft_memcpy(tmp2, env->img + end, pad);
	// 	ft_memcpy(env->img + start, tmp2, pad);
	// 	ft_memcpy(env->img + end, tmp1, pad);

	// 	// t = env->img[length - i];
	// 	// env->img[length - i] = env->img[i];
	// 	// env->img[i] = t;

	// 	// pad = sizeof(unsigned char);
	// 	// ft_memcpy(&t, &env->img[length - i], pad);
	// 	// ft_memcpy(&env->img[length - i], &env->img[i], pad);
	// 	// ft_memcpy(&env->img[i], &t, pad);
	// }
}

static int  load_img(t_env *env)
{
	env->img = load_bmp("./ressources/images/texture.bmp", &env->img_w, &env->img_h);
	reverse_image(env);
    return (env->img ? 0 : -1);
}

int			gl_textures(t_env *env)
{
    glGenTextures(1, &env->tex);
    glBindTexture(GL_TEXTURE_2D, env->tex);

    glUniform1i(glGetUniformLocation(env->shader_program, "tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (load_img(env) < 0)
		return (-1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->img_w, env->img_h, 0, GL_BGR, GL_UNSIGNED_BYTE, env->img);

    // Black/white checkerboard
    // float pixels[] = {
    //     1.f, 1.f, 1.f,   0.f, 0.f, 0.f,
    //     0.f, 0.f, 0.f,   0.f, 0.f, 0.f
    // };
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
	return (0);
}
