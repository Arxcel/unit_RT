/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:41:28 by anestor           #+#    #+#             */
/*   Updated: 2018/03/19 18:01:34 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

static void	render_background(t_main *m)
{
	SDL_RenderCopy(m->sdl.ren, m->ui.bg[LEFT_FRAME].textr,
						NULL, &m->ui.bg[LEFT_FRAME].rect);
	SDL_RenderCopy(m->sdl.ren, m->ui.bg[RIGHT_FRAME].textr,
						NULL, &m->ui.bg[RIGHT_FRAME].rect);
	SDL_RenderCopy(m->sdl.ren, m->ui.bg[LOGO].textr,
						NULL, &m->ui.bg[LOGO].rect);
	ui_render_corners(&m->ui, &m->sdl, m->ui.scene_place);
	ui_render_corners(&m->ui, &m->sdl, m->ui.bg[LEFT_FRAME].rect);
	ui_render_corners(&m->ui, &m->sdl, m->ui.bg[RIGHT_FRAME].rect);
	ui_render_lines(&m->ui, &m->sdl);
}

static void render_buttons(t_main *m)
{
	SDL_RenderCopy(m->sdl.ren, (m->ui.btn[OPEN].status == 1)
				? m->ui.btn[OPEN].on : m->ui.btn[OPEN].off,
							NULL, &m->ui.btn[OPEN].rect);
	SDL_RenderCopy(m->sdl.ren, (m->ui.btn[SAVE].status == 1)
				? m->ui.btn[SAVE].on : m->ui.btn[SAVE].off,
							NULL, &m->ui.btn[SAVE].rect);
	SDL_RenderCopy(m->sdl.ren, (m->ui.btn[SAVE_AS].status == 1)
				? m->ui.btn[SAVE_AS].on : m->ui.btn[SAVE_AS].off,
							NULL, &m->ui.btn[SAVE_AS].rect);
	SDL_RenderCopy(m->sdl.ren, (m->ui.btn[EXPORT].status == 1)
				? m->ui.btn[EXPORT].on : m->ui.btn[EXPORT].off,
							NULL, &m->ui.btn[EXPORT].rect);
}

void	render_scene_and_ui(t_main *m)
{
	ui_bg_rect_params(&m->ui, &m->sdl);
	ui_btn_rect_params(&m->ui, &m->sdl);
	SDL_RenderCopy(m->sdl.ren, m->ui.bg[BACKGROUND].textr,
						NULL, &m->ui.bg[BACKGROUND].rect);
	re_draw(&m->cl, &m->sdl, &m->s);
	SDL_UpdateTexture(m->sdl.texture, NULL,
			m->sdl.img.pixels, m->sdl.img.w * sizeof(unsigned int));
	sdl_clear_image(&m->sdl.img);
	SDL_RenderCopy(m->sdl.ren, m->sdl.texture, NULL, &m->ui.scene_place);
	render_background(m);
	render_buttons(m);
	SDL_RenderPresent(m->sdl.ren);
}

void	ui_and_sdl_init(t_main *m)
{
	m->cl.work_dim[0] = WIN_W - R_SCENE_W_TRIM;
	m->cl.work_dim[1] = WIN_H - R_SCENE_H_TRIM;
	m->sdl.win_w = WIN_W;
	m->sdl.win_h = WIN_H;
	sdl_init(&m->sdl);
	sdl_recreate_img(&m->sdl.img, m->sdl.win_w - R_SCENE_W_TRIM,
									m->sdl.win_h - R_SCENE_H_TRIM);
	SDL_DestroyTexture(m->sdl.texture);
	m->sdl.texture = SDL_CreateTexture(m->sdl.ren,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STATIC,
								m->sdl.win_w - R_SCENE_W_TRIM,
								m->sdl.win_h - R_SCENE_H_TRIM);
//	ui_rect_params(&m->ui, &m->sdl);
	ui_textures_init(&m->ui, &m->sdl);
	ui_buttons_init(&m->ui, &m->sdl);
	SDL_SetWindowMinimumSize(m->sdl.win, 800, 600);
}

void	window_resized_event(t_main *m)
{
	m->sdl.win_w = m->sdl.e.window.data1;
	m->sdl.win_h = m->sdl.e.window.data2;
	m->cl.work_dim[0] = m->sdl.win_w - R_SCENE_W_TRIM;
	m->cl.work_dim[1] = m->sdl.win_h - R_SCENE_H_TRIM;
	sdl_recreate_img(&m->sdl.img, m->sdl.win_w - R_SCENE_W_TRIM,
									m->sdl.win_h - R_SCENE_H_TRIM);
	SDL_DestroyTexture(m->sdl.texture);
	m->sdl.texture = SDL_CreateTexture(m->sdl.ren,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STATIC,
								m->sdl.win_w - R_SCENE_W_TRIM,
								m->sdl.win_h - R_SCENE_H_TRIM);
//	ui_rect_params(&m->ui, &m->sdl);
	m->sdl.changes = 1;
}

void	ui_btn_rect_params(t_ui *ui, t_sdl *sdl)
{
	ui->btn[OPEN].rect =
		sdl_rect(BTN_ROW1_X, BTN_ROW1_Y, BTN_SIZE, BTN_SIZE);
	ui->btn[SAVE].rect =
		sdl_rect(BTN_ROW1_X * 2 + BTN_SIZE / 1.8, BTN_ROW1_Y, BTN_SIZE, BTN_SIZE);
	ui->btn[SAVE_AS].rect =
		sdl_rect(BTN_ROW1_X * 3 + BTN_SIZE / 1.8 * 2, BTN_ROW1_Y, BTN_SIZE, BTN_SIZE);
	ui->btn[EXPORT].rect =
		sdl_rect(BTN_ROW1_X * 4 + BTN_SIZE / 1.8 * 3, BTN_ROW1_Y, BTN_SIZE, BTN_SIZE);
	(void)sdl;
}

void	ui_bg_rect_params(t_ui *ui, t_sdl *sdl)
{
	ui->scene_place = sdl_rect(R_SCENE_X, R_SCENE_Y, sdl->img.h, sdl->img.w);
	ui->bg[BACKGROUND].rect = sdl_rect(0, 0, sdl->win_h, sdl->win_w);
	ui->bg[LEFT_FRAME].rect = sdl_rect(5, R_SCENE_Y,
				sdl->win_h - R_SCENE_Y - 5, L_FRAME_W);
	ui->bg[RIGHT_FRAME].rect = sdl_rect(sdl->win_w - R_FRAME_W - 5,
				R_SCENE_Y, sdl->win_h - R_SCENE_Y - 5, R_FRAME_W);
	ui->bg[LOGO].rect = sdl_rect(sdl->win_w - (LOGO_W + 10),
				5, LOGO_H, LOGO_W);
}

void	ui_textures_init(t_ui *ui, t_sdl *sdl)
{
	ui->bg[BACKGROUND].textr =
		sdl_texture_from_file("textures/background.png", sdl->ren);
	ui->bg[LEFT_FRAME].textr =
		sdl_texture_from_file("textures/left_frame.png", sdl->ren);
	ui->bg[RIGHT_FRAME].textr =
		sdl_texture_from_file("textures/right_frame.png", sdl->ren);
	ui->bg[LT_CORNER].textr =
		sdl_texture_from_file("textures/left_top_corner.png", sdl->ren);
	ui->bg[LB_CORNER].textr =
		sdl_texture_from_file("textures/left_bot_corner.png", sdl->ren);
	ui->bg[RT_CORNER].textr =
		sdl_texture_from_file("textures/right_top_corner.png", sdl->ren);
	ui->bg[RB_CORNER].textr =
		sdl_texture_from_file("textures/right_bot_corner.png", sdl->ren);
	ui->bg[BL_DOT].textr =
		sdl_texture_from_file("textures/black_dot.png", sdl->ren);
	ui->bg[DG_DOT].textr =
		sdl_texture_from_file("textures/dark_grey_dot.png", sdl->ren);
	ui->bg[LG_DOT].textr =
		sdl_texture_from_file("textures/light_grey_dot.png", sdl->ren);
	ui->bg[CO_DOT].textr =
		sdl_texture_from_file("textures/contrast_dot.png", sdl->ren);
	ui->bg[LOGO].textr =
		sdl_texture_from_file("textures/logo_small.png", sdl->ren);
}
