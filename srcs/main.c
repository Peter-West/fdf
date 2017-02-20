#include "fdf.h"
#include <stdio.h>

void		fill_struct(t_point **points, char *line)
{
	static int		y = 0;
	int				x;
	t_point			*point;
	char			**split;
	int				i;

	i = 0;
	x = 0;
	split = ft_strsplit(line, ' ');
	while (split[i])
	{
		point = (t_point*)malloc(sizeof(t_point));
		point->val = ft_atoi(split[i]);
		point->x = x++ * SPACE_INBETWEEN;
		point->y = y * SPACE_INBETWEEN;
		point->next = NULL;
		fill_list(points, point);
		i++;
	}
	y++;
}

void		fill_list(t_point **points, t_point *point)
{
	t_point	*tmp;
	t_point	*new_p;

	new_p = point;
	if (!(*points))
		*points = new_p;
	else
	{
		tmp = *points;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_p;

	}
}

void		read_map(t_env *e, char *name)
{
	char	*line;
	int		fd;

	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		fill_struct(&e->points, line);
	}
}

void		init_mlx(t_env *e)
{
	if (!(e->mlx_ptr = mlx_init()))
		ft_putstr("init mlx failed\n");
	e->img_ptr = mlx_new_image(e->mlx_ptr, 500, 500);
	e->win_ptr = mlx_new_window(e->mlx_ptr, 500, 500, "FDF" );
}

int			key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 0x24)
		exit(1);
	return (0);
}

void		draw_lines(t_env *e)
{
	t_point	*tmp;
	int		x;
	int		color;

	tmp = e->points;
	color = 3010730;
	while (tmp)
	{
		if (tmp->next && tmp->next->x == tmp->x + SPACE_INBETWEEN)
		{
			x = tmp->x;
			while (x < tmp->next->x)
				mlx_pixel_put (e->mlx_ptr, e->win_ptr, x++, tmp->y , color);
		}
		tmp = tmp->next;
	}
}

void		draw_columns(t_env *e)
{
	t_point	*tmp;
	int		y;
	int		color;

	tmp = e->points;
	color = 3010730;
	while (tmp)
	{
		if (tmp->next && tmp->next->y == tmp->y + SPACE_INBETWEEN)
		{
			y = tmp->y;
			while (y < tmp->next->y)
				mlx_pixel_put (e->mlx_ptr, e->win_ptr, tmp->x, y++, color);
		}
		tmp = tmp->next;
	}
}

int			expose_hook(t_env *e)
{
	t_point	*tmp;

	tmp = e->points;
	draw_lines(e);
	draw_columns(e);
/*	while (tmp)
	{
		// color = (tmp->val > 0) ? 11816618 : 11842730;
		// if (tmp->val < 0)
		tmp = tmp->next;
	}*/
	// mlx_put_image_to_window (e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
	return (0);
}

void		loop(t_env *e)
{
	mlx_key_hook (e->win_ptr, key_hook, NULL);
	mlx_expose_hook (e->win_ptr, expose_hook, e);
	mlx_loop(e->mlx_ptr);
}

void		debug(t_env *e)
{
	t_point	*tmp;

	tmp = e->points;
	while (tmp)
	{
		printf("point : %d, y : %d, x : %d\n", tmp->val, tmp->y, tmp->x);
		tmp = tmp->next;
	}
}

int			main(int argc, char **argv)
{
	t_env		e;

	if (argc != 2)
	{
		ft_putstr("usage : ./fdf [map]\n");
		exit(1);
	}
	read_map(&e, argv[1]);
	// debug(&e);
	init_mlx(&e);
	loop(&e);
	return (0);
}