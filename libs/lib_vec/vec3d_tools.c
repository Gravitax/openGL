/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:18:43 by gedemais          #+#    #+#             */
/*   Updated: 2022/08/15 17:13:22 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

float	ft_rsqrt(float number)
{
	float	i;
	float	threehalfs;
	u_rsqrt	conv;

	i = number * 0.5f;
	threehalfs = 1.5f;
	conv = (u_rsqrt){ number };
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (i * conv.f * conv.f));
	return (1 / conv.f);
}

vec3	zero_vector(void)
{
	return ((vec3){0.0f, 0.0f, 0.0f, 0.0f});
}

float	vec_norm(vec3 vec)
{
	return (ft_rsqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

vec3	vec_normalize(vec3 vec)
{
	float	l;

	l = vec_norm(vec);
	return ((vec3){vec.x /= l, vec.y /= l, vec.z /= l, vec.w /= l});
}

float	vec_dot(vec3 a, vec3 b)
{
	float	ret;

	ret = 0.0f;
	ret += a.x * b.x;
	ret += a.y * b.y;
	ret += a.z * b.z;
	return (ret);
}

float	vec3d_dist(vec3 o, vec3 v)
{
	return (ft_rsqrt((o.x - v.x) * (o.x - v.x)
		+ (o.y - v.y) * (o.y - v.y)
		+ (o.z - v.z) * (o.z - v.z)));
}

bool	vec_outrange(vec3 dim, vec3 pos)
{
	return (pos.x < 0 || pos.x > dim.x - 1
		|| pos.y < 0 || pos.y > dim.y - 1
		|| pos.z < 0 || pos.z > dim.z - 1);
}

void	vec3d_swap(vec3 *a, vec3 *b)
{
	vec3	t;

	t = *a;
	*a = *b;
	*b = t;
}

vec3	abs_vector(vec3 vec)
{
	return ((vec3){fabs(vec.x), fabs(vec.y), fabs(vec.z), fabs(vec.w)});
}
