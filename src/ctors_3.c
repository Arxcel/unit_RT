/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctors_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:35:55 by afarapon          #+#    #+#             */
/*   Updated: 2018/03/26 00:14:35 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_light				default_parallel(void)
{
	t_light			result;

	ft_bzero(&result, sizeof(t_light));
	result.type = L_PAR;
	result.color = (t_vector){0.8, 0.8, 0.8};
	result.pos = (t_vector){-0.5, -0.5, -0.5};
	result.dir = (t_vector){0, -1, 0};
	result.intence = 1;
	return (result);
}

t_light				default_lamp(void)
{
	t_light			result;

	ft_bzero(&result, sizeof(t_light));
	result.type = L_LAMP;
	result.color = (t_vector){0.8, 0.8, 0.8};
	result.pos = (t_vector){0, 2, 0};
	result.intence = 1;
	return (result);
}

t_light				default_area(void)
{
	t_light			result;

	ft_bzero(&result, sizeof(t_light));
	result.type = L_AREA;
	result.color = (t_vector){0.8, 0.8, 0.8};
	result.pos = (t_vector){-0.5, -0.5, -0.5};
	result.dir = (t_vector){0, -1, 0};
	result.ang = 45;
	result.intence = 1;
	return (result);
}

t_light				default_ambient(void)
{
	t_light			result;

	ft_bzero(&result, sizeof(t_light));
	result.type = L_AMBIENT;
	result.color = (t_vector){0.8, 0.8, 0.8};
	result.intence = 0.2;
	return (result);
}

t_light				default_light(void)
{
	t_light			result;

	ft_bzero(&result, sizeof(t_light));
	result.type = -1;
	return (result);
}
