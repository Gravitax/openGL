#include "main.h"


unsigned char		*read_bmp(FILE *file, unsigned char *header, int *width, int *height)
{
	int				w;
	int				h;
	unsigned char	*data;
	int				image_size;
	int				data_pos;

	data_pos = *(int *)&(header[0x0A]);
	image_size = *(int *)&(header[0x22]);
	w = *(int *)&(header[0x12]);
	h = *(int *)&(header[0x16]);
	*width = w;
	*height = h;
	if (image_size == 0)
		image_size = w * h * 3;
	if (data_pos == 0)
		data_pos = 54;
	if (!(data = (unsigned char *)ft_memalloc(sizeof(unsigned char) * image_size)))
		scop_exit();
	fread(data, 1, image_size, file);
	fclose(file);
	return (data);
}

unsigned char		*load_bmp(char const *pathname, int *width, int *height)
{
	FILE			*file;
	unsigned char	header[54];

	file = fopen(pathname, "rb");
	if (!file || fread(header, 1, 54, file) != 54)
		scop_exit();
	if (header[0] != 'B' || header[1] != 'M')
		scop_exit();
	return (read_bmp(file, header, width, height));
}

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (load_img(env) < 0)
		return (-1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->img_w, env->img_h,
    	    0, GL_BGR, GL_UNSIGNED_BYTE, env->img);

    // Black/white checkerboard
    // float pixels[] = {
    //     1.f, 1.f, 1.f,   0.f, 0.f, 0.f,
    //     0.f, 0.f, 0.f,   0.f, 0.f, 0.f
    // };
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);
	return (0);
}
