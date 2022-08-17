#include "../../../includes/main.h"


/*
	1  0  0  0
	0  C -S  0
	0  S  C  0
	0  0  0  1
*/
void		mat4_xrotation(mat4 m, float x) //
{
	mat4_identity(m);
	m[5] = cosf(x);
	m[6] = -sinf(x);
	m[9] = sinf(x);
	m[10] = cosf(x);
}

/*
	C  0  S  0
	0  1  0  0
	-S 0  C  0
	0  0  0  1	
*/
void		mat4_yrotation(mat4 m, float y) //
{
	mat4_identity(m);
	m[0] = cosf(y);
	m[2] = sinf(y);
	m[8] = -sinf(y);
	m[10] = cosf(y);
}

/*	
	C -S  0  0
	S  C  0  0
	0  0  1  0
	0  0  0  1
*/
void		mat4_zrotation(mat4 m, float z)
{
	mat4_identity(m);
	m[0] = cosf(z);
	m[1] = -sinf(z);
	m[4] = sinf(z);
	m[5] = cosf(z);
}

/* x: pitch, y:yaw, z:roll, applied yaw->pitch->roll in relative coordonates */
void		mat4_rotate(mat4 m, float x, float y, float z)
{
	mat4	rot_x, rot_y, rot_z;

	mat4_xrotation(rot_x, x);
	mat4_yrotation(rot_y, y);
	mat4_zrotation(rot_z, z);
	mat4_multiply(m, rot_y);
	mat4_multiply(m, rot_x);
	mat4_multiply(m, rot_z);
}

void		mat4_rotation(mat4 m, vec3 axis, float angle)
{
	float	cos, sin;

	angle = (float)ft_to_radians(angle);
	cos = cosf(angle);
	sin = sinf(angle);

	mat4_identity(m);

	m[0] = cos + axis.x * axis.x * (1.0 - cos);
	m[1] = axis.x * axis.y * (1.0 - cos) + axis.z * sin;
	m[2] = axis.x * axis.z * (1.0 - cos) - axis.y * sin;
	m[4] = axis.x * axis.y * (1.0 - cos) - axis.z * sin;
	m[5] = cos + axis.y * axis.y * (1.0 - cos);
	m[6] = axis.y * axis.z * (1.0 - cos) + axis.x * sin;
	m[8] = axis.x * axis.z * (1.0 - cos) + axis.y * sin;
	m[9] = axis.y * axis.z * (1.0 - cos) - axis.x * sin;
	m[10] = cos + axis.z * axis.z * (1.0 - cos);

	// m[0] = cos + axis.x * axis.x * (1.0 - cos);
	// m[4] = axis.x * axis.y * (1.0 - cos) + axis.z * sin;
	// m[8] = axis.x * axis.z * (1.0 - cos) - axis.y * sin;
	// m[1] = axis.x * axis.y * (1.0 - cos) - axis.z * sin;
	// m[5] = cos + axis.y * axis.y * (1.0 - cos);
	// m[9] = axis.y * axis.z * (1.0 - cos) + axis.x * sin;
	// m[2] = axis.x * axis.z * (1.0 - cos) + axis.y * sin;
	// m[6] = axis.y * axis.z * (1.0 - cos) - axis.x * sin;
	// m[10] = cos + axis.z * axis.z * (1.0 - cos);
}
