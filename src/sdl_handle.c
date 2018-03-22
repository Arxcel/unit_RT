/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:01:54 by vkozlov           #+#    #+#             */
/*   Updated: 2018/03/22 19:41:24 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

static void			pos_camera(int key, t_main *m)
{
	if (key == SDLK_w)
		m->s.cam_trans.pos[2] -= 10;
	else if (key == SDLK_s)
		m->s.cam_trans.pos[2] += 10;
	else if (key == SDLK_a)
		m->s.cam_trans.pos[0] -= 10;
	else if (key == SDLK_d)
		m->s.cam_trans.pos[0] += 10;
	else if (key == SDLK_q)
		m->s.cam_trans.pos[1] += 10;
	else if (key == SDLK_e)
		m->s.cam_trans.pos[1] -= 10;
}

static void			rot_camera(int key, t_main *m)
{
	if (key == SDLK_i)
		m->s.cam_trans.rot[0] += 5;
	else if (key == SDLK_k)
		m->s.cam_trans.rot[0] -= 5;
	else if (key == SDLK_j)
		m->s.cam_trans.rot[1] += 5;
	else if (key == SDLK_l)
		m->s.cam_trans.rot[1] -= 5;
	else if (key == SDLK_u)
		m->s.cam_trans.rot[2] += 5;
	else if (key == SDLK_o)
		m->s.cam_trans.rot[2] -= 5;
}

static void			key_down(int key, t_main *m)
{
	if (key == SDLK_ESCAPE)
		m->sdl.running = 0;
	else if (key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d
				|| key == SDLK_q || key == SDLK_e)
	{
		pos_camera(key, m);
		m->sdl.changes = 1;
	}
	else if (key == SDLK_i || key == SDLK_k || key == SDLK_j || key == SDLK_l
				|| key == SDLK_u || key == SDLK_o)
	{
		rot_camera(key, m);
		m->sdl.changes = 1;
	}
	else if (key == SDLK_z)
	{
		open_file(m);
	}
	else if (key == SDLK_KP_1)
	{
		m->after_effect ^= AE_SEPIA;
		m->sdl.changes = 1;
	}
	else if (key == SDLK_KP_2)
	{
		m->after_effect ^= AE_TOON;
		m->sdl.changes = 1;
	}
	else if (key == SDLK_KP_3)
	{
		m->after_effect ^= AE_M_BLUR;
		m->sdl.changes = 1;
	}
	else if (key == SDLK_KP_4)
	{
		m->after_effect ^= AE_SMOOTH;
		m->sdl.changes = 1;
	}
	else if (key == SDLK_KP_5)
	{
		m->after_effect ^= AE_CONTR;
		m->sdl.changes = 1;
	}
	else if (key == SDLK_KP_PLUS || key == SDLK_KP_MINUS)
	{
		m->coeficient = key == SDLK_KP_PLUS ? m->coeficient + 1 : m->coeficient - 1;
		if (m->after_effect & AE_CONTR)
			m->sdl.changes++;
	}
	else if (key == SDLK_KP_6)
	{
		m->after_effect ^= AE_SHARPNESS;
		m->sdl.changes = 1;
	}
}

void				sdl_loop(t_main *m)
{
	while (m->sdl.running)
	{
		sdl_hook(m);
		if (m->sdl.changes)
		{
			re_draw(&m->cl, &m->sdl, &m->s);
			set_filter(m);
			render_scene_and_ui(m);
			m->sdl.changes = 0;
		}
	}
}

void				sdl_hook(t_main *m)
{
	while (SDL_PollEvent(&m->sdl.e) != 0)
	{
		if (m->sdl.e.type == SDL_QUIT)
			m->sdl.running = 0;
		else if (m->sdl.e.type == SDL_WINDOWEVENT)
		{
			if (m->sdl.e.window.event == SDL_WINDOWEVENT_RESIZED)
				window_resized_event(m);
		}
		else if (m->sdl.e.type == SDL_KEYDOWN)
			key_down(m->sdl.e.key.keysym.sym, m);
		else if (m->sdl.e.type == SDL_MOUSEBUTTONDOWN)
				mouse_down(m->sdl.e.button.x, m->sdl.e.button.y, m);
		else if (m->sdl.e.type == SDL_MOUSEBUTTONUP)
			mouse_up(m->sdl.e.button.x, m->sdl.e.button.y, m);
	}
}
