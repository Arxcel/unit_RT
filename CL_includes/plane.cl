/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 11:57:00 by vkozlov           #+#    #+#             */
/*   Updated: 2018/02/09 11:57:00 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

short				plane_cross(t_object *p, t_ray *r, float *t)
{
	float a;
	float t0;
	t_vector v;

	a = v_dot(p->dir, r->dir);
	if (a != 0)
	{
        v = p->point - r->orig; 
        t0 = v_dot(v, p->dir) / a;
		if (t0 >= 0)
		{
			r->n_hit[0] = a;
			*t = t0;
        	return (1); 
		}
    }
	return (0);
}

short				get_plane_data(t_ray *ray, t_object plane, float t)
{
	ray->p_hit = ray->orig + v_mult_d(ray->dir, t);
	ray->n_hit = ray->n_hit[0] && ray->n_hit[0] < 0 ? plane.dir : -plane.dir;
	return (1);
}
