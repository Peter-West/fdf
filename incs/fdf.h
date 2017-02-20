#ifndef FDF_H
# define FDF_H
# define SPACE_INBETWEEN	30
# include "libft.h"
# include "get_next_line.h"
# include <mlx.h>
# include <fcntl.h>

typedef struct		s_point
{
	int				val;
	int				x;
	int				y;
	struct s_point	*next;
}					t_point;

typedef struct		s_env
{
	t_point			*points;
	void	*mlx_ptr;
	void	*img_ptr;
	void	*win_ptr;
}					t_env;

void		fill_list(t_point **points, t_point *point);
void		read_map(t_env *e, char *name);
void		fill_struct(t_point **points, char *line);


#endif