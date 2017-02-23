#include "fdf.h"

int			expose_hook(t_env *e)
{
	render(e);
	return (0);
}

int			key_pressed_hook(int keycode, t_env *e)
{
	if (keycode == K_RETURN || keycode == K_Q)
		exit(1);
	if (keycode == K_RIGHT_ARROW)
		e->buttons.right = 1;
	if (keycode == K_LEFT_ARROW)
		e->buttons.left = 1;
	if (keycode == K_DOWN_ARROW)
		e->buttons.down = 1;
	if (keycode == K_UP_ARROW)
		e->buttons.up = 1;
	if (keycode == K_W)
		e->buttons.zoom_in = 1;
	if (keycode == K_S)
		e->buttons.zoom_out = 1;
	if (keycode == K_A)
		e->buttons.rotate_left = 1;
	if (keycode == K_D)
		e->buttons.rotate_right = 1;
	return (0);
}

int			key_released_hook(int keycode, t_env *e)
{
	if (keycode == K_RIGHT_ARROW)
		e->buttons.right = 0;
	if (keycode == K_LEFT_ARROW)
		e->buttons.left = 0;
	if (keycode == K_DOWN_ARROW)
		e->buttons.down = 0;
	if (keycode == K_UP_ARROW)
		e->buttons.up = 0;
	if (keycode == K_W)
		e->buttons.zoom_in = 0;
	if (keycode == K_S)
		e->buttons.zoom_out = 0;
	if (keycode == K_A)
		e->buttons.rotate_left = 0;
	if (keycode == K_D)
		e->buttons.rotate_right = 0;
	return (0);
}

int			loop_hook(t_env *e)
{
	if (e->buttons.right)
		move_right(e);
	if (e->buttons.left)
		move_left(e);
	if (e->buttons.up)
		move_up(e);
	if (e->buttons.down)
		move_down(e);
	if (e->buttons.zoom_in)
		zoom_in(e);
	if (e->buttons.zoom_out)
		zoom_out(e);
	if (e->buttons.rotate_left)
		rotate_left(e);
	if (e->buttons.rotate_right)
		rotate_right(e);
	return (0);
}
