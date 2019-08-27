/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:10:55 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/27 19:33:53 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_player(t_dm *dm, int fd)
{
	char	*tmp;
	char	**split;
	char	**split2;

	malloc_check(dm, dm->pl = (t_pl*)malloc(sizeof(t_pl)));
	get_next_line(fd, &tmp);
	while (tmp[0] != 'p')
	{
		if (!get_next_line(fd, &tmp))
			close_app("Error with map!");
	}
	split = ft_strsplit(tmp, 9);
	split2 = ft_strsplit(split[1], ' ');
	dm->pl->pos.x = ft_atoi(split2[0]);
	dm->pl->pos.y = ft_atoi(split2[1]);
	dm->pl->angle = ft_atoi(split2[2]);
	free_split(split2);
	dm->pl->sect = ft_atoi(split[2]);
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
	dm->nverts = 0;
	dm->nsects = 0;
	dm->up = 0;
	dm->down = 0;
	dm->right = 0;
	dm->left = 0;
	dm->strafel = 0;
	dm->strafer = 0;
}

void	init_sect(t_dm *dm)
{
	read_map(dm, "test_map");
	/*
	dm->sect.pts = (t_v2*)malloc(sizeof(t_v2) * 5);
	dm->sect.pts[0] = new_v2(200.0, 100.0);
	dm->sect.pts[1] = new_v2(0.0, 100.0);
	dm->sect.pts[2] = new_v2(100.0, 200.0);
	dm->sect.pts[3] = new_v2(500.0, 200.0);
	dm->sect.pts[4] = new_v2(200.0, 100.0);
	dm->sect.numpts = 5;
	*/
	/*
	dm->sect.pts = (t_v2*)malloc(sizeof(t_v2) * 2);
	dm->sect.pts[0] = new_v2(200.0, 200.0);
	dm->sect.pts[1] = new_v2(400.0, 400.0);
	dm->sect.numpts = 2;
*/
}

t_dm	*init_dm(int ac, char **av)
{
	t_dm *dm;

	(void)ac;
	(void)av;
	malloc_check(NULL, dm = (t_dm*)malloc(sizeof(t_dm)));
	init_const(dm);
	init_sect(dm);
	malloc_check(dm, dm->sdl = (t_sdl*)malloc(sizeof(t_sdl)));
	prepare_window(dm);
	update(dm, 0);
	return (dm);
}
