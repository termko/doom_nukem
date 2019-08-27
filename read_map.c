/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:24:08 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/27 19:39:42 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	init_verts(t_dm *dm, int fd)
{
	int		i;
	char	*tmp;
	char	**split;

	malloc_check(NULL, dm->verts = (t_v2*)malloc(sizeof(t_v2) * dm->nverts));
	i = 0;
	while (i < dm->nverts)
	{
		get_next_line(fd, &tmp);
		if (tmp[0] != 'v')
			continue ;
		split = ft_strsplit(tmp, 9);
		if (!split[1] || !split[2])
			close_app("Error with vertices!");
		dm->verts[i].x = ft_atoi(split[1]);
		dm->verts[i].y = ft_atoi(split[2]);
		free_split(split);
		free(tmp);
		i++;
	}
}

void	init_sects(t_dm *dm, int fd)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	**split;
	char	**split2;
	
	malloc_check(NULL, dm->sects = (t_sect*)malloc(sizeof(t_sect) * dm->nsects));
	i = 0;
	while (i < dm->nsects)
	{
		get_next_line(fd, &tmp);
		if (tmp[0] != 's')
			continue ;
		split = ft_strsplit(tmp, 9);
		if (!split[1] || !split[2] || !split[3])
			close_app("Error with sectors!");
		split2 = ft_strsplit(split[1], ' ');
		dm->sects[i].floor = ft_atoi(split2[0]);
		dm->sects[i].ceil = ft_atoi(split2[1]);
		j = 0;
		free_split(split2);
		split2 = ft_strsplit(split[2], ' ');
		len = 0;
		while (split2[len])
			len++;
		dm->sects[i].numpts = len + 1;
		malloc_check(NULL, dm->sects[i].pts = (t_v2*)malloc(sizeof(t_v2) * (len + 1)));
		while (j < len)
		{
			dm->sects[i].pts[j] = dm->verts[ft_atoi(split2[j])];
			j++;
		}
		dm->sects[i].pts[j] = dm->sects[i].pts[0];
		free_split(split2);
		split2 = ft_strsplit(split[3], ' ');
		malloc_check(NULL, dm->sects[i].neigh = (int*)malloc(sizeof(int) * (len + 1)));
		j = 0;
		while (j < len)
		{
			dm->sects[i].neigh[j] = ft_atoi(split2[j]);
			j++;
		}
		dm->sects[i].neigh[j] = dm->sects[i].neigh[0];
		free_split(split2);
		free_split(split);
		free(tmp);
		i++;
	}
}

void	first_read(t_dm *dm, char *file)
{
	char	*tmp;
	int		fd;
	int		pl;

	pl = 0;
	fd = open(file, 'r');
	while (get_next_line(fd, &tmp))
	{
		if (tmp[0] == 'v')
			dm->nverts++;
		else if (tmp[0] == 's')
			dm->nsects++;
		else if (tmp[0] == 'p')
			pl++;
		free(tmp);
	}
	if (!dm->nverts || !dm->nsects || pl != 1)
		close_app("ERROR WITH MAP!");
	close(fd);
}

void	read_map(t_dm *dm, char *file)
{
	int		fd;
	int		i;
	int		j;

	first_read(dm, file);
	i = 0;
	j = 0;
	fd = open(file, 'r');
	init_verts(dm, fd);
	init_sects(dm, fd);
	init_player(dm, fd);
}
