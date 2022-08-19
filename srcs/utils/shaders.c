#include "../../includes/main.h"


void		shaders(t_gltools *gl)
{
	gl->shader_vertex_text =
		"#version 400\n"
		"\n"
		"layout (location = 0) in vec4	in_position;\n"
		"layout (location = 1) in vec4	in_color;\n"
		"layout (location = 2) in vec2	in_texcoord;\n"
		"layout (location = 3) in vec3	in_normal;\n"
		"\n"
		"uniform mat4	model;\n"
		"uniform mat4	view;\n"
		"uniform mat4	projection;\n"
		"\n"
 		"out vec4	Color;\n"
		"out vec3	Normal;\n"
 		"out vec4	Position;\n"
		"out vec2	Texcoord;\n"
		"\n"
		"void	main()\n"
		"{\n"
		"	Color		= in_color;\n"
		"	Normal		= in_normal * mat3(transpose(inverse(model)));\n"
		// "	Normal		= in_normal;\n"
		"	Position	= in_position * model;\n"
		"	Texcoord	= in_texcoord;\n"
		"\n"
		"	gl_Position = in_position * model * view * projection;\n"
		"}\n";
	gl->shader_fragment_text =
		"#version 400\n"
		"\n"
		"struct	Light {\n"
		"	vec4	pos, color;\n"
		"	vec4	ambient, diffuse, specular;\n"
		"};\n"
		"\n"
		"\n"
		"in vec4	Color;\n"
		"in vec3	Normal;\n"
		"in vec4	Position;\n"
		"in vec2	Texcoord;\n"
		"\n"
		"uniform Light		light;"
		"uniform sampler2D	texture_color;\n"
		"uniform vec4		campos;\n"
		"uniform int		mode;\n"
		"\n"
		"out vec4	FragColor;\n"
		"\n"
		"void	main()\n"
		"{\n"
		"	switch (mode) {\n" // ==========================================
		"		case (0): \n" // ONLY COLOR
		"			FragColor = Color;\n"
		"			break ;\n" // ==========================================
		"		case (1): \n" // ONLY TEXTURE
		"			FragColor = texture(texture_color, Texcoord);\n"
		"			break ;\n" // ==========================================
		"		case (2): case (3):\n" // LIGHT COLOR / TEXTURE
		"			vec4	color = mode == 2 ? light.color : texture(texture_color, Texcoord).rgba;\n"
		"			\n" // ambient
		"			vec4	ambient		= color * light.ambient;\n"
		"			\n" // diffuse
		"			vec3	n			= normalize(Normal);\n"
		"			vec3	light_dir	= vec3(normalize(light.pos - Position));\n"
		"			float	diff		= max(dot(n, light_dir), 0);\n"
		"			vec4	diffuse		= color * light.diffuse * diff;\n"
		"			\n" // specular
		"			vec3	view_dir	= vec3(normalize(campos - Position));\n"
		"			vec3	reflect_dir	= reflect(-light_dir, n);\n"
		"			float	spec		= pow(max(dot(view_dir, reflect_dir), 0), 32);\n"
		"			vec4	specular	= color * light.specular * spec;\n"
		"			\n"
		"			FragColor = (ambient + diffuse + specular);\n"
		"			if (mode == 2) FragColor *= Color;\n"
		"			break ;\n" // ==========================================
		"	}\n"
		"}\n";
}
