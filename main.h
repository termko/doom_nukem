/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/27 19:45:17 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "SDL2/SDL.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

typedef struct	s_v3
{
	float		x;
	float		y;
	float		z;
}				t_v3;

typedef struct	s_sect
{
	double		floor;
	double		ceil;
	t_v2		*pts;
	int			*neigh;
	int			numpts;
}				t_sect;

typedef struct	s_pl
{
	t_v3	pos;
	t_v3	vel;
	double	angle;
	double	fov;
	double	height;
	int		speed;
	int		turn;
	int		sect;
}				t_pl;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*sf;
	SDL_Event		evt;
	SDL_Renderer	*ren;
	SDL_Texture		*txt;
	Uint32			*pix;
}				t_sdl;

typedef struct	s_dm
{
	t_sdl		*sdl;
	t_pl		*pl;
	t_sect		*sects;
	t_sect		sect;
	t_v2		*verts;
	int			nverts;
	int			nsects;
	int			width;
	int			height;
	int			left;
	int			right;
	int			up;
	int			down;
	int			strafel;
	int			strafer;
	int			shift;
}				t_dm;

int		close_app(char *str);
void	simclose(const char *str);
t_dm	*init_dm(int ac, char **av);
void	init_player(t_dm *dm, int fd);
void	read_map(t_dm *dm, char *file);
int		cycle(t_dm *dm);
void	update(t_dm *wf, int flag);
void	malloc_check(t_dm *dm, void *addr);
t_v2	new_v2(double x, double y);
void	draw(t_dm *dm);
void	movement(t_dm *dm);
void	turn_left(t_dm *dm);
void	turn_right(t_dm *dm);
double	degtorad(double deg);
double	radtodeg(double rad);
double	min(double a, double b);
double	max(double a, double b);
t_v2	intersect(t_v2 a, t_v2 b, t_v2 c, t_v2 d);
void	free_split(char **split);
#endif
