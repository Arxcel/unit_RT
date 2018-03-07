/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:57:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/09 11:57:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

short				disk_cross(t_object *d, t_ray *r, float *t)
{
//	float a;
//	float b;
//	float t0;
//	t_vector	point;
//
//	if (!(a = v_dot(d->dir, r->dir)))
///		return (0);
//	b = -(v_dot(d->dir, r->orig) + d->p);
//	if ((t0 = b / a) > 0.000001)
//	{
//		r->p_hit = r->orig + v_mult_d(r->dir, t0);
//		point = v_mult_d(d->dir, d->p);
//		point = r->p_hit - point;//(t_vector){0,0,d->p};
//		if (d->radius * d->radius >= v_dot(point, point))
///		{
//			*t = t0;
//			return (1);
//		}
//	}
//	return (0);

	float a;
	float t0;
	t_vector v;

	a = v_dot(d->dir, r->dir);
	if (a > 0)
	{
        v = d->point - r->orig; 
        t0 = v_dot(v, d->dir) / a;
		if (t0 >= 0)
		{
			r->p_hit = r->orig + v_mult_d(r->dir, t0);
			v = r->p_hit - d->point;
			if (d->radius * d->radius >= v_dot(v, v))
			{
				*t = t0;
				return (1);
			}
		}
    }
	return (0);
}

short				get_disk_data(t_ray *ray, t_object disk, float t)
{
	ray->n_hit = -disk.dir;
	ray->n_hit = v_normalize(ray->n_hit);
	return (1);
}