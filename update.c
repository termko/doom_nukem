/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:21:20 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/20 14:53:19 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_x(t_dm *dm, t_v2 p1, t_v2 p2)
{
	int		x;
	int		y;
	double	eps;
	double	m;

	x = p1.x;
	y = p1.y;
	m = fabs(1 / ((p2.x - p1.x) / (p2.y - p1.y)));
	eps = m - 1;
	while (x != (int)p2.x)
	{
		if (500 + x >= 0 && 500 + x < dm->width && 500 + y >= 0 && 500 + y < dm->height)
			dm->sdl->pix[500 + x + (500 + y) * dm->width] = 0x0000ff;
		p2.x < p1.x ? x-- : x++;
		eps += m;
		if (eps > 0)
		{
			p2.y < y ? y-- : y++;
			eps--;
		}
	}
}

void	draw_y(t_dm *dm, t_v2 p1, t_v2 p2)
{
	int		x;
	int		y;
	double	eps;
	double	m;

	x = p1.x;
	y = p1.y;
	m = fabs((p2.x - p1.x) / (p2.y - p1.y));
	eps = m - 1;
	while (y != (int)p2.y)
	{
		if (500 + x >= 0 && 500 + x < dm->width && 500 + y >= 0 && 500 + y < dm->height)
			dm->sdl->pix[500 + x + (500 + y) * dm->width] = 0x0000ff;
		p2.y < p1.y ? y-- : y++;
		eps += m;
		if (eps > 0)
		{
			p2.x < x ? x-- : x++;
			eps--;
		}
	}
}

void	draw(t_dm *dm)
{
	int i;
	int j;
	t_v3 tmp1;
	t_v3 tmp2;
	t_v3 p1;
	t_v3 p2;
	
	i = 0;
	while (i < dm->width)
	{
		j = 0;
		while (j < dm->height)
		{
			dm->sdl->pix[i + j * dm->width] = 0xffffff;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < dm->sect.numpts - 1)
	{
		printf("%d\n", i);
		tmp1.x = dm->sect.pts[i].x;
		tmp1.y = dm->sect.pts[i].y;
		
		/*
		if (i == dm->sect.numpts - 1)
		{
			tmp2.x = dm->sect.pts[0].x;
			tmp2.y = dm->sect.pts[0].y;
		}
		else
		{
			tmp2.x = dm->sect.pts[i + 1].x;
			tmp2.y = dm->sect.pts[i + 1].y;
		}
		*/
	
		tmp2.x = dm->sect.pts[i + 1].x;
		tmp2.y = dm->sect.pts[i + 1].y;

		tmp1.x -= dm->pl->pos.x;
		tmp1.y -= dm->pl->pos.y;
		tmp2.x -= dm->pl->pos.x;
		tmp2.y -= dm->pl->pos.y;

	// DELETE AFTER
		double psin = sin(degtorad(dm->pl->angle));
		double pcos = cos(degtorad(dm->pl->angle));

		p1.x = tmp1.x * psin - tmp1.y * pcos;
		p1.z = tmp1.x * pcos + tmp1.y * psin;
		p2.x = tmp2.x * psin - tmp2.y * pcos;
		p2.z = tmp2.x * pcos + tmp2.y * psin;

		if (p1.z <= 0 && p2.z <= 0)
		{
			printf("NOT IN FRONT!!! %f %f\n", p1.z, p2.z);
			i++;
			continue ;
		}
	
	/*	
		fabs(p1.x - p2.x) <= fabs(p1.z - p2.z) ?
							 draw_y(dm, new_v2(p1.x, p1.z), new_v2(p2.x, p2.z)) :
							 draw_x(dm, new_v2(p1.x, p1.z), new_v2(p2.x, p2.z));
		i++;
	*/

		if (dm->right || dm->left || dm->up || dm->down || dm->strafel || dm->strafer)
		{
			printf("PL POS = (%f : %f)\nPL ANGLE = %f\nWALL POS = (%f : %f) -> (%f : %f)\n", dm->pl->pos.x, dm->pl->pos.y, dm->pl->angle, p1.x, p1.y, p2.x, p2.y);
		}
		//TRANSFER THOSE TO THE TOP!!!
		t_v2	intr1;
		t_v2	intr2;
		t_v2	topl;
		t_v2	topr;
		t_v2	botl;
		t_v2	botr;

		if (p1.z <= 0 || p2.z <= 0)
		{
			printf("PARTIALLY BEHIND!!!\n%f %f\n", p1.z, p2.z);
			intr1 = intersect(new_v2(p1.x, p1.z), new_v2(p2.x, p2.z), new_v2(-1e-4f, 1e-4f), new_v2(-20, 5));
			intr2 = intersect(new_v2(p1.x, p1.z), new_v2(p2.x, p2.z), new_v2(1e-4f, 1e-4f), new_v2(20, 5));

			if (p1.z <= 0)
			{
				if (intr1.y > 0)
				{
					p1.x = intr1.x;
					p1.z = intr1.y;
				}
				else
				{
					p1.x = intr2.x;
					p1.z = intr2.y;
				}
			}

			if (p2.z <= 0)
			{
				if (intr1.y > 0)
				{
					p2.x = intr1.x;
					p2.z = intr1.y;
				}
				else
				{
					p2.x = intr2.x;
					p2.z = intr2.y;
				}
			}
		}
			printf("PL POS = (%f : %f)\nPL ANGLE = %f\nWALL POS = (%f : %f) -> (%f : %f)\n", dm->pl->pos.x, dm->pl->pos.y, dm->pl->angle, p1.x, p1.z, p2.x, p2.z);
		if (dm->right || dm->left || dm->up || dm->down || dm->strafel || dm->strafer)
		{
		//	printf("FIRST INTERSECT = (%f : %f)\nSECOND INTERSECT = (%f : %f)\n", intr1.x, intr1.y, intr2.x, intr2.y);
		}

		topl.x = -p1.x * 256 / p1.z;
		topl.y = -3500 / p1.z;

		topr.x = -p2.x * 256 / p2.z;
		topr.y = -3500 / p2.z;
		
		botl.x = topl.x;
		botl.y = 3500 / p1.z;

		botr.x = topr.x;
		botr.y = 3500 / p2.z;

		printf("PRINTING...\n");
		printf("topl -> (%f %f)\ntopr -> (%f %f)\nbotl = (%f %f)\nbotr = (%f %f)\n", topl.x, topl.y, topr.x, topr.y, botl.x, botl.y, botr.x, botr.y);
		fabs(topl.x - topr.x) <= fabs(topl.y - topr.y) ?
							 draw_y(dm, topl, topr) :
							 draw_x(dm, topl, topr);
	
		fabs(topr.x - botr.x) <= fabs(topr.y - botr.y) ?
							 draw_y(dm, topr, botr) :
							 draw_x(dm, topr, botr);

		fabs(botl.x - botr.x) <= fabs(botl.y - botr.y) ?
							 draw_y(dm, botl, botr) :
							 draw_x(dm, botl, botr);

		fabs(topl.x - botl.x) <= fabs(topl.y - botl.y) ?
							 draw_y(dm, topl, botl) :
							 draw_x(dm, topl, botl);

		printf("DONE PRINTING!\n");
		i++;
	}
	
	update(dm, 0);
}

void	update(t_dm *dm, int flag)
{
	if (flag)
		ft_memset(dm->sdl->pix, 0, dm->width * dm->height * sizeof(Uint32));
	if (SDL_UpdateTexture(dm->sdl->txt, NULL, dm->sdl->pix,
			dm->width * sizeof(Uint32)))
		simclose("Unexpected error with SDL.");
	if (SDL_RenderClear(dm->sdl->ren))
		simclose("Unexpected error with SDL.");
	if (SDL_RenderCopy(dm->sdl->ren, dm->sdl->txt, NULL, NULL))
		simclose("Unexpected error with SDL.");
	SDL_RenderPresent(dm->sdl->ren);
}
