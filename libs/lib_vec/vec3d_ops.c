/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:10:39 by gedemais          #+#    #+#             */
/*   Updated: 2022/08/15 17:12:52 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

vec3		vec_add(vec3 a, vec3 b)
{
	vec3	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	ret.w = a.w + b.w;
	return (ret);
}

vec3		vec_sub(vec3 a, vec3 b)
{
	vec3	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	ret.w = a.w - b.w;
	return (ret);
}

vec3		vec_mult(vec3 a, vec3 b)
{
	vec3	ret;

	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	ret.w = a.w * b.w;
	return (ret);
}

vec3		vec_div(vec3 a, vec3 b)
{
	vec3	ret;

	ret.x = a.x / b.x;
	ret.y = a.y / b.y;
	ret.z = a.z / b.z;
	ret.w = a.w / b.w;
	return (ret);
}

vec3		vec_relu(vec3 v)
{
	if (fabs(v.x) == 0.0f || fabs(v.y) == 0.0f || fabs(v.z) == 0.0f)
		v = zero_vector();
	return (v);
}
