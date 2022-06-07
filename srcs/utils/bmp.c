#include "main.h"


static unsigned char	*read_bmp(FILE *file, unsigned char *header, int *width, int *height)
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

unsigned char			*load_bmp(char const *pathname, int *width, int *height)
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
