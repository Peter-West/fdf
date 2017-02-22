#ifndef FDF_H
# define FDF_H
# define SPACE_INBETWEEN	30
# define COLOR_UP			16714390
# define COLOR_DOWN			3010730
# define COLOR_STEP			(16714390 - 3010730) / 30
# define K_RIGHT_ARROW		0x7C
# define K_Q				0x0C
# define K_W				0x0D
# define K_S				0x01
# define K_LEFT_ARROW		0x7B
# define K_DOWN_ARROW		0x7D
# define K_UP_ARROW			0x7E
# define K_RETURN			0x24
# include "libft.h"
# include "get_next_line.h"
# include <mlx.h>
# include <X11/Xlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>


typedef struct		s_point
{
	int				z;
	int				x;
	int				y;
	struct s_point	*next;
}					t_point;

typedef struct		s_buttons
{
	int				up;
	int				down;
	int				right;
	int				left;
	int				zoom_in;
	int				zoom_out;
}					t_buttons;

typedef struct		s_env
{
	t_point			*points;
	t_buttons		buttons;
	void			*mlx_ptr;
	void			*img_ptr;
	void			*win_ptr;
	int				z_min;
	int				z_max;
	int				scale;
}					t_env;

void		fill_list(t_point **points, t_point *point);
void		read_map(t_env *e, char *name);
void		fill_struct(t_point **points, char *line);
void		move_right(t_env *e);
void		move_down(t_env *e);
void		move_left(t_env *e);
void		move_up(t_env *e);
void		render(t_env *e);
int			expose_hook(t_env *e);
int			loop_hook(t_env *e);
int			key_pressed_hook(int keycode, t_env *e);
int			key_released_hook(int keycode, t_env *e);
void		zoom_in(t_env *e);
void		zoom_out(t_env *e);


#endif