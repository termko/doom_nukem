/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:12:18 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 15:30:45 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move_up(t_dm *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x += cos(degtorad(wf->pl->angle));
	y += sin(degtorad(wf->pl->angle));
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	move_down(t_dm *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x -= cos(degtorad(wf->pl->angle));
	y -= sin(degtorad(wf->pl->angle));
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	strafe_right(t_dm *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x += cos(degtorad(wf->pl->angle - 90));
	y += sin(degtorad(wf->pl->angle - 90));
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	strafe_left(t_dm *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x += cos(degtorad(wf->pl->angle + 90));
	y += sin(degtorad(wf->pl->angle + 90));
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	movement(t_dm *dm)
{
	if (dm->up)
		move_up(dm);
	if (dm->down)
		move_down(dm);
	if (dm->right)
		turn_right(dm);
	if (dm->left)
		turn_left(dm);
	if (dm->strafer)
		strafe_right(dm);
	if (dm->strafel)
		strafe_left(dm);
}
