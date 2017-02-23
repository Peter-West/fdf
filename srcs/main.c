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
		fill_struct(&e->points, line);
}

void		init_mlx(t_env *e)
{
	if (!(e->mlx_ptr = mlx_init()))
		ft_putstr("init mlx failed\n");
	e->img_ptr = mlx_new_image(e->mlx_ptr, 1000, 1000);
	e->win_ptr = mlx_new_window(e->mlx_ptr, 1000, 1000, "FDF");
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

void		img_to_win(t_env *e)
{
	int		size_line = 1000;
	int		bits_per_pixel = 32;
	int		endian = 0;	
	char	*data;

	data = mlx_get_data_addr(e->img_ptr, &bits_per_pixel, &size_line, &endian);
	printf("img : %s\n, ptr : %p, size : %ld\n", data, data, sizeof(data));
	size_line = 100;
	data = mlx_get_data_addr(e->img_ptr, &bits_per_pixel, &size_line, &endian);
	printf("img : %s\n, ptr : %p\n", data, data);

	int color_value = mlx_get_color_value (e->mlx_ptr, 0);
	printf("color_value : %d\n", color_value);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}

void		test_rotation_2d_lines(t_env *e, int x, int y, int z)
{
	double		xp, yp;
	int		color;
	
	color = (z == 0) ? 0xFFFFFF : 0xFF0000;
	// xp = (cos(e->theta) * x) - (sin(e->theta) * y);
	// yp = (sin(e->theta) * x) + (cos(e->theta) * y);
	// printf("x : %d,y : %d\n", x, y);
	xp = 0.71 * (x - y);
	yp = (0.41 * (x + y)) + (0.82 * z);
	// printf("lines : x : %d, xp : %f\n", x, xp);
	// printf("lines : y : %d, yp : %f\n", y, yp);
	mlx_pixel_put (e->mlx_ptr, e->win_ptr, xp, yp * e->scale, color);

}

void		test_rotation_2d_col(t_env *e, int x, int y, int z)
{
	double		xp, yp;
	int		color;
	
	(void)e;
	color = (z == 0) ? 0xFFFFFF : 0xFF0000;
	// xp = (cos(e->theta) * x) - (sin(e->theta) * y);
	// yp = (sin(e->theta) * x) + (cos(e->theta) * y);
	// printf("col : x : %d, xp : %d\n", x, xp);
	// printf("col : y : %d, yp : %d\n", y, yp);
	// printf("x : %d,y : %d\n", x, y);
	xp = 0.71 * (x - y);
	yp = (0.41 * (x + y)) + (0.82 * z);
	// mlx_pixel_put (e->mlx_ptr, e->win_ptr, xp * e->scale, yp, color);
}

void		draw_lines(t_env *e)
{
	t_point		*tmp;
	double		x;
	// int			color;

	tmp = e->points;
	while (tmp)
	{
		if (tmp->next && tmp->next->x == tmp->x + 1)
		{
			// color = color_start(e, tmp->z);
			x = tmp->x * e->scale;
			while (x < tmp->next->x * e->scale)
			{
				// color = color_start(e, tmp->z, x - tmp->x);
				//mlx_pixel_put (e->mlx_ptr, e->win_ptr, x++, tmp->y * e->scale, color);
				test_rotation_2d_lines(e, x++, tmp->y, tmp->z);
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
	// int		color;

	tmp = e->points;
	while (tmp)
	{
		tmp2 = e->points;
		while(tmp2)
		{
			if (tmp->x == tmp2->x && tmp->y + 1 == tmp2->y)
			{
				y = tmp->y * e->scale;
				while (y < tmp2->y * e->scale)
				{
					// color = color_start(e, tmp->z, y - tmp->y);
					// color = 0xFFFFFF;
					// color = (tmp->z == 0) ? 0xFFFFFF : 0xFF0000;
					// mlx_pixel_put(e->mlx_ptr, e->win_ptr, tmp->x * e->scale, y++, color);
					test_rotation_2d_col(e, tmp->x, y++, tmp->z);
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
	// draw_lines(e);
	// draw_columns(e);
	img_to_win(e);
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
	e->theta = 0.0;
	e->buttons.up = 0;
	e->buttons.down = 0;
	e->buttons.right = 0;
	e->buttons.left = 0;
	e->buttons.zoom_in = 0;
	e->buttons.zoom_out = 0;
	e->buttons.rotate_left = 0;
	e->buttons.rotate_right = 0;
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
	// debug(&e);
	init_mlx(&e);
	loop(&e);
	return (0);
}