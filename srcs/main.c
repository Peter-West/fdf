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

void		min_max(t_env *e)
{
	t_point	*tmp;

	tmp = e->points;
	e->z_min = 0;
	e->z_max = 0;
	while (tmp)
	{
		if (tmp->val < e->z_min)
			tmp->val = e->z_min;
		if (tmp->val < e->z_max)
			tmp->val = e->z_max;
		tmp = tmp->next;
	}
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

	if (!(fd = open(name, O_RDONLY)))
	{
		ft_putstr("Can't open file\n");
		exit(1);
	}
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

int			color_change(int val_start, int val_end)
{
	if (val_start == val_end)
		return (0);
	if (val_start > 0 && val_end > 0)
		return (COLOR_UP);
	if (val_start > 0 && val_end < 0)

	if (val_start > 0 && val_end == 0)
	
	if (val_start < 0 && val_end == 0)

	if (val_start < 0 && val_end > 0)

	if (val_start < 0 && val_end < 0)
		return (COLOR_DOWN);
	

		return ((COLOR_BASE - COLOR_UP) / SPACE_INBETWEEN);
	if (val < 0)
	{
		// printf("check : %d\n", (COLOR_BASE - COLOR_DOWN) / SPACE_INBETWEEN);
		return ((COLOR_BASE - COLOR_DOWN) / SPACE_INBETWEEN);
	}
	return (0);
}

int		color_start(t_env *e, int z_val, int step)
{
	/*if (val_start == e->z_max)
		return (COLOR_UP);
	if (val_start == e->z_min)
		return (COLOR_DOWN);
	*/
	return (COLOR_DOWN + (COLOR_STEP * (z_val - val_curr)));
}

void		draw_lines(t_env *e)
{
	t_point	*tmp;
	int		x;
	int		color;

	tmp = e->points;
	while (tmp)
	{
		if (tmp->next && tmp->next->x == tmp->x + SPACE_INBETWEEN)
		{
			color = color_start(e, tmp->val);
			x = tmp->x;
			while (x < tmp->next->x)
			{
				printf("color : %d\n", color);
				// color -= color_change(tmp->val, tmp->next->val);
				color = color_start(e, tmp->val);

				mlx_pixel_put (e->mlx_ptr, e->win_ptr, x++, tmp->y , color);
			}
		}
		tmp = tmp->next;
	}
}

void		draw_columns(t_env *e)
{
	t_point	*tmp;
	t_point	*tmp2;
	int		y;
	int		color;

	tmp = e->points;
	while (tmp)
	{
		tmp2 = e->points;
		while(tmp2)
		{
			if (tmp->x == tmp2->x && tmp->y + SPACE_INBETWEEN == tmp2->y)
			{
				y = tmp->y;
				color = color_start(e, tmp->val);
				while (y < tmp2->y)
				{
					color -= color_change(tmp->val, tmp2->val);
					mlx_pixel_put (e->mlx_ptr, e->win_ptr, tmp->x, y++, color);
				}
			}
			tmp2 = tmp2->next;
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
	min_max(&e);
	printf("z_min : %d, z_max : %d\n", e.z_min, e.z_max);
	init_mlx(&e);
	loop(&e);
	return (0);
}