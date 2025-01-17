/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_fops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:51:11 by gedemais          #+#    #+#             */
/*   Updated: 2022/08/15 17:12:36 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"

vec3		vec_fdiv(vec3 a, float n)
{
	vec3	ret;

	ret.x = a.x / n;
	ret.y = a.y / n;
	ret.z = a.z / n;
	ret.w = a.w / n;
	return (ret);
}

vec3		vec_fmult(vec3 a, float n)
{
	vec3	ret;

	ret.x = a.x * n;
	ret.y = a.y * n;
	ret.z = a.z * n;
	ret.w = a.w * n;
	return (ret);
}

vec3		vec_fadd(vec3 a, float n)
{
	vec3	ret;

	ret.x = a.x + n;
	ret.y = a.y + n;
	ret.z = a.z + n;
	ret.w = a.w + n;
	return (ret);
}

vec3		vec_fsub(vec3 a, float n)
{
	vec3	ret;

	ret.x = a.x - n;
	ret.y = a.y - n;
	ret.z = a.z - n;
	ret.w = a.w - n;
	return (ret);
}

vec3		vec_cross(vec3 a, vec3 b)
{
	vec3	ret;

	ret.x = (a.y * b.z) - (a.z * b.y);
	ret.y = (a.z * b.x) - (a.x * b.z);
	ret.z = (a.x * b.y) - (a.y * b.x);
	return (ret);
}
