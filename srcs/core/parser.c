#include "../../includes/main.h"


static size_t	next_line(const char *str, size_t current)
{
	size_t	next;

	next = 0;
	while (str[current + next] != 0 && str[current + next] != '\n')
		++next;
	if (str[current + next] != 0)
		++next;
	return (next);
}

static size_t	next_char(const char *str, size_t current)
{
	size_t	next;

	next = 0;
	while (str[current + next] != 0 && str[current + next] == ' ')
		++next;
	return (next);
}

/* ########################################################################## */

static int		parse_vertex(t_env *env, const char *str, size_t current)
{
	static const float	color_palette[6] = {0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f};
	static int			current_color = 0;

	static unsigned		current_vertex = 0;
	unsigned			number_num;

	number_num = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		env->parser.vertex[current_vertex + (number_num++)] = (GLfloat)atof(str + current);

		if (str[current] == '-')
			++current;
		while (ft_isdigit(str[current]) || str[current] == '.')
			++current;
		current += next_char(str, current);
		if (number_num > 3 || (str[current] != 0 && str[current] != '\n' &&
			str[current] != '-' && !ft_isdigit(str[current])))
		{
			printf("Parsing error, invalid vertex (number %d)\n", number_num);
			return (-1);
		}
	}
	if (number_num != 3)
	{
		printf("Parsing error, invalid vertex (%d numbers)\n", number_num);
		return (-1);
	}
	env->parser.vertex[current_vertex + 3] = color_palette[current_color++ % 6];
	// env->parser.vertex[current_vertex + 3] = 1;
	current_vertex += 4;
	return (0);
}

static void		parse_element(t_env *env, const char *str, size_t current)
{
	static unsigned	current_element = 0;
	GLuint			tmp[4];
	int				number_vertex;

	number_vertex = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		tmp[number_vertex++] = (GLuint)atoi(str + current);
		while (ft_isdigit(str[current]))
			++current;
		current += next_char(str, current);
	}
	for (unsigned i = 0; i < 3; ++i)
		env->parser.element[current_element + i] = tmp[i] - 1;
	current_element += 3;
	if (number_vertex == 4)
	{
		for (unsigned i = 0; i < 3; ++i)
			env->parser.element[current_element + i] = tmp[(i + 2) % 4] - 1;
		current_element += 3;
	}
}

/* ########################################################################## */

/* to differenciate triangles from rectangle elements */
static int		element_type(const char *str, size_t current)
{
	int	number_vertex;

	number_vertex = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		++number_vertex;
		while (ft_isdigit(str[current]))
			++current;
		if (str[current] == 0 || str[current] == ' ')
			current += next_char(str, current);
		else if (str[current] == '\n')
			break ;
		else
		{
			printf("Parsing error, invalid element [%c]\n", str[current]);
			return (-1);
		}
	}
	if (number_vertex != 3 && number_vertex != 4)
	{
		printf("Parsing error, invalid element (%d vertex)\n", number_vertex);
		return (-1);
	}
	return (number_vertex == 3 ? 1 : 2);
}

/* initialize vertex and element data sizes and malloc them */
static int		init_sizes(t_parser *parser, const char *str)
{
	size_t		current;
	int			type;

	current = 0;
	while (str[current])
	{
		switch (str[current])
		{
			case 'v' :
				++parser->vertex_size;
				break ;
			case 'f' :
				type = element_type(str, current + 1);
				if (type == -1)
					return (-1);
				parser->element_size += type;
				break ;
			case '#' : case 'm' : case 'o' : case 's' : case 'u' : case '\n' :
				break ;
			default :
				printf("Parsing error: invalid line >%c<\n", str[current]);
				return (-1);
		}
		current += next_line(str, current);
	}
	parser->vertex_size *= sizeof(float) * 4;
	parser->element_size *= sizeof(unsigned int) * 3;
	parser->vertex = ft_memalloc((size_t)parser->vertex_size);
	parser->element = ft_memalloc((size_t)parser->element_size);
	return ((!parser->vertex || !parser->element) ? -1 : 0);
}

/* ########################################################################## */

static void		print_result(t_env *env)
{
	int		vsize = env->parser.vertex_size / (sizeof(float) * 4);
	int		esize = env->parser.element_size / (sizeof(unsigned int) * 3);
	int		i;

	printf("VERTICES ---------------------\n");
	for (i = 0; i < vsize; i += 4) {
		printf("[%f, %f, %f, %f]\n",
			env->parser.vertex[i], env->parser.vertex[i + 1], env->parser.vertex[i + 2], env->parser.vertex[i + 3]);
	}
	printf("ELEMENTS ---------------------\n");
	for (i = 0; i < esize; i+= 3) {
		printf("[%d | %d | %d]\n",
			env->parser.element[i], env->parser.element[i + 1], env->parser.element[i + 2]);
	}
	printf("Loaded %d vertices and %d triangles\n", vsize, esize / 3);
}

int				parse_obj(t_env *env, char *filename)
{
	const char	*file;
	size_t		current;

	if ((file = ft_readfile(filename)) == NULL)
		return (-1);
	if (init_sizes(&env->parser, file) < 0)
		return (-1);
	current = 0;
	while (file[current])
	{
		if (file[current] == 'v' && parse_vertex(env, file, current + 1) < 0)
		{
			free((void *)file);
			return(-1);
		}
		else if (file[current] == 'f')
			parse_element(env, file, current + 1);
		current += next_line(file, current);
	}
	free((void *)file);
	print_result(env);
	return (0);
}
