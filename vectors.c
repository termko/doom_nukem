/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 11:43:41 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 11:44:14 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_v2	new_v2(double x, double y)
{
	t_v2 ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}
