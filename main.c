/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:10:57 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 13:25:13 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int close_app(char *str)
{
	ft_putendl(str);
	SDL_Quit();
	return (0);
}

void simclose(const char *str)
{
	ft_putendl(str);
	SDL_Quit();
}

void	malloc_check(t_dm *dm, void *addr)
{
	if (!addr)
	{
		if (dm)
			exit(close_app("Unexpected error with malloc! Exiting..."));
		SDL_Quit();
		ft_putendl("Unexpected error with malloc! Exiting...");
		exit(1);
	}
}

int main(int ac, char **av)
{
	return (cycle(init_dm(ac, av)));
}
