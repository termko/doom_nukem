/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:10:55 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 18:02:09 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_player(t_dm *dm)
{
	malloc_check(dm, dm->pl = (t_pl*)malloc(sizeof(t_pl)));
	dm->pl->pos = new_v2(500, 500);
	dm->pl->angle = 315;
	dm->pl->fov = 60;
	dm->pl->turn = 90;
	dm->pl->speed = 90;
	dm->pl->height = dm->height / 2;
}

void	prepare_window(t_dm *wf)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		simclose(SDL_GetError());
	if (!(wf->sdl->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, wf->width, wf->height, 0)))
		simclose(SDL_GetError());
	if (!(wf->sdl->ren = SDL_CreateRenderer(wf->sdl->win, -1, 0)))
		simclose(SDL_GetError());
	if (!(wf->sdl->txt = SDL_CreateTexture(wf->sdl->ren,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
			wf->width, wf->height)))
		simclose(SDL_GetError());
	malloc_check(wf, wf->sdl->pix = (Uint32*)malloc(sizeof(Uint32) *
				(wf->width * wf->height)));
	update(wf, 1);
}

void	init_const(t_dm *dm)
{
	dm->width = 1000;
	dm->height = 1000;
	dm->up = 0;
	dm->down = 0;
	dm->right = 0;
	dm->left = 0;
	dm->strafel = 0;
	dm->strafer = 0;
}

void	init_sect(t_dm *dm)
{
/*
	dm->sect.pts = (t_v2*)malloc(sizeof(t_v2) * 4);
	dm->sect.pts[0] = new_v2(200.0, 300.0);
	dm->sect.pts[1] = new_v2(300.0, 300.0);
	dm->sect.pts[2] = new_v2(300.0, 200.0);
	dm->sect.pts[3] = new_v2(200.0, 200.0);
	dm->sect.numpts = 4;
*/
	dm->sect.pts = (t_v2*)malloc(sizeof(t_v2) * 2);
	dm->sect.pts[0] = new_v2(200.0, 200.0);
	dm->sect.pts[1] = new_v2(400.0, 400.0);
	dm->sect.numpts = 2;
}

t_dm	*init_dm(int ac, char **av)
{
	t_dm *dm;

	(void)ac;
	(void)av;
	malloc_check(NULL, dm = (t_dm*)malloc(sizeof(t_dm)));
	init_const(dm);
	init_sect(dm);
	init_player(dm);
	malloc_check(dm, dm->sdl = (t_sdl*)malloc(sizeof(t_sdl)));
	prepare_window(dm);
	update(dm, 0);
	return (dm);
}
