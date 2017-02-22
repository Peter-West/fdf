#include "fdf.h"

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
		point->z = ft_atoi(split[i]);
		point->x = x++;
		point->y = y;
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
		if (e->z_min > tmp->z)
			e->z_min = tmp->z;
		if (e->z_max < tmp->z)
			e->z_max = tmp->z;
		tmp = tmp->next;
	}
	printf("z_min : %d, z_max : %d\n", e->z_min, e->z_max);
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
	e->img_ptr = mlx_new_image(e->mlx_ptr, 1000, 1000);
	e->win_ptr = mlx_new_window(e->mlx_ptr, 1000, 1000, "FDF" );
}

/*
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
}*/

int		color_start(t_env *e, int z, int step)
{
	/*if (val_start == e->z_max)
		return (COLOR_UP);
	if (val_start == e->z_min)
		return (COLOR_DOWN);
	*/
	return (COLOR_DOWN + ((COLOR_STEP * step) * (z + e->z_min)));
}

void		draw_lines(t_env *e)
{
	t_point	*tmp;
	int		x;
	int		color;

	tmp = e->points;
	while (tmp)
	{
		if (tmp->next && tmp->next->x == tmp->x + 1)
		{
			// color = color_start(e, tmp->z);
			x = tmp->x;
			while (x < tmp->next->x)
			{
				// printf("color : %d\n", color);
				// color = color_start(e, tmp->z, x - tmp->x);
				color = 0xFFFFFF;
				mlx_pixel_put (e->mlx_ptr, e->win_ptr, x++ * e->scale, tmp->y * e->scale, color);
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
			if (tmp->x == tmp2->x && tmp->y + 1 == tmp2->y)
			{
				y = tmp->y;
				while (y < tmp2->y)
				{
					// color = color_start(e, tmp->z, y - tmp->y);
					color = 0xFFFFFF;
					mlx_pixel_put(e->mlx_ptr, e->win_ptr, tmp->x * e->scale, y++ * e->scale, color);
				}
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void		render(t_env *e)
{
	mlx_clear_window(e->mlx_ptr, e->win_ptr);
	draw_lines(e);
	draw_columns(e);
	// mlx_put_image_to_window (e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}

void		loop(t_env *e)
{
	// XButtonPressedEvent		key_pressed;
	// XButtonReleasedEvent	key_released;

	// mlx_key_hook (e->win_ptr, key_hook, e);
	mlx_expose_hook (e->win_ptr, expose_hook, e);
	mlx_loop_hook(e->mlx_ptr, loop_hook, e);
	mlx_hook(e->win_ptr, KeyPress, KeyPressMask, key_pressed_hook, e);
	mlx_hook(e->win_ptr, KeyRelease, KeyReleaseMask, key_released_hook, e);
	mlx_loop(e->mlx_ptr);
}

void		debug(t_env *e)
{
	t_point	*tmp;

	tmp = e->points;
	while (tmp)
	{
		printf("point : %d, y : %d, x : %d\n", tmp->z, tmp->y, tmp->x);
		tmp = tmp->next;
	}
}

void		init(t_env *e)
{
	e->points = NULL;
	e->scale = SPACE_INBETWEEN;
	e->buttons.up = 0;
	e->buttons.down = 0;
	e->buttons.right = 0;
	e->buttons.left = 0;
	e->buttons.zoom_in = 0;
	e->buttons.zoom_out = 0;
}

int			main(int argc, char **argv)
{
	t_env		e;

	if (argc != 2)
	{
		ft_putstr("usage : ./fdf [map]\n");
		exit(1);
	}
	init(&e);
	read_map(&e, argv[1]);
	min_max(&e);
	debug(&e);
	init_mlx(&e);
	loop(&e);
	return (0);
}