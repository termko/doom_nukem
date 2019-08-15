/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/08/15 16:34:24 by ydavis           ###   ########.fr       */
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
# define SQLEN 64
# define TXT_BRICK	0
# define TXT_WOOD	1
# define TXT_STONE	2
# define TXT_IMG	3
# define TXT_VENT_1	4
# define TXT_VENT_2	5
# define TXT_FLOOR	6
# define TXT_LAMP	10
# define TXT_BOX	11
# define TXT_HEALTH	12
# define TXT_SKY	20

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
	t_v2		*pts;
	int			numpts;
}				t_sect;

typedef struct	s_pl
{
	t_v2	pos;
	double	angle;
	double	fov;
	double	height;
	int		speed;
	int		turn;
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
	t_sect		sect;
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
#endif
