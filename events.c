/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:23:00 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 13:34:21 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_keys(t_dm *wf, SDL_Event evt, int key)
{
	if (SDLK_LEFT == evt.key.keysym.sym)
		wf->left = key;
	else if (SDLK_RIGHT == evt.key.keysym.sym)
		wf->right = key;
	else if (SDLK_UP == evt.key.keysym.sym || SDLK_w == evt.key.keysym.sym)
		wf->up = key;
	else if (SDLK_DOWN == evt.key.keysym.sym || SDLK_s == evt.key.keysym.sym)
		wf->down = key;
	else if (SDLK_a == evt.key.keysym.sym)
		wf->strafel = key;
	else if (SDLK_d == evt.key.keysym.sym)
		wf->strafer = key;
	else if (SDLK_LSHIFT == evt.key.keysym.sym)
		wf->shift = key;
}

void	handle_events(t_dm *dm)
{
	SDL_Event	evt;

	while (SDL_PollEvent(&evt))
	{
		if ((SDL_QUIT == evt.type) || (SDL_KEYDOWN == evt.type &&
					SDL_SCANCODE_ESCAPE == evt.key.keysym.scancode))
			exit(close_app("App was closed."));
		if (SDL_KEYDOWN == evt.type)
			check_keys(dm, evt, 1);
		if (SDL_KEYUP == evt.type)
			check_keys(dm, evt, 0);
	}
	draw(dm);
}

int		cycle(t_dm *dm)
{
	while (1)
	{
		handle_events(dm);
		movement(dm);
	}
	return (0);
}
