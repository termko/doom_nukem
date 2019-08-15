/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:57:21 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 18:16:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	vxs(double ax, double ay, double bx, double by)
{
	return (ax * by - bx * ay);
}

int		overlap(double a0, double a1, double b0, double b1)
{
	return (min(a0, a1) <= max(b0, b1) && min(b0, b1) <= max(a0, a1));
}

int		intersectbox(t_v2 a, t_v2 b, t_v2 c, t_v2 d)
{
	return (overlap(a.x, b.x, c.x, d.x) && overlap(a.y, b.y, c.y, d.y));
}

int		pointside(t_v2 p, t_v2 a, t_v2 b)
{
	return (vxs(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y));
}

t_v2	intersect(t_v2 a, t_v2 b, t_v2 c, t_v2 d)
{
	t_v2 ret;
	double x;
	double y;
	double det;

	x = vxs(a.x, a.y, b.x, b.y);
	y = vxs(c.x, c.y, d.x, d.y);
	det = vxs(a.x - b.x, a.y - b.y, c.x - d.x, c.y - d.y);
	x = vxs(x, a.x - b.x, y, c.x - d.x) / det;
	y = vxs(x, a.y - b.y, y, c.y - d.y) / det;
	ret.x = x;
	ret.y = y;
	/*
	ret.x = vxs(vxs(a.x, a.y, b.x, b.y),
			a.x - b.x, vxs(c.x, c.y, d.x, d.y),
			c.x - d.x) /
		vxs(a.x - b.x, a.y - b.y, c.x - d.x, c.y - d.y);
	ret.y = vxs(vxs(a.x, a.y, b.x, b.y),
			a.y - b.y, vxs(c.x, c.y, d.x, d.y),
			c.y - d.y) /
		vxs(a.x - b.x, a.y - b.y, c.x - d.x, c.y - d.y);
	*/
	return (ret);
}
