#include "fdf.h"

void			move_right(t_env *e)
{
	t_point		*tmp;
	
	tmp = e->points;
	while (tmp)
	{
		tmp->x = tmp->x + 1;
		tmp = tmp->next;
	}
	render(e);
}

void			move_left(t_env *e)
{
	t_point		*tmp;
	
	tmp = e->points;
	while (tmp)
	{
		tmp->x = tmp->x - 1;
		tmp = tmp->next;
	}
	render(e);
}

void			move_down(t_env *e)
{
	t_point		*tmp;
	
	tmp = e->points;
	while (tmp)
	{
		tmp->y = tmp->y + 1;
		tmp = tmp->next;
	}
	render(e);
}

void			move_up(t_env *e)
{
	t_point		*tmp;
	
	tmp = e->points;
	while (tmp)
	{
		tmp->y = tmp->y - 1;
		tmp = tmp->next;
	}
	render(e);
}

void			zoom_in(t_env *e)
{
	e->scale++;
	render(e);
}

void			zoom_out(t_env *e)
{
	if (e->scale > 0)
		e->scale--;
	render(e);
}