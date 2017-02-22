#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 17:52:30 by ppellegr          #+#    #+#              #
#    Updated: 2015/06/04 17:52:30 by ppellegr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME				:= fdf
SRCS				:= main.c translation.c events.c
PATH_OBJ			:= objs
PATH_SRC			:= srcs
PATH_INC			:= incs
CXX					:= gcc
CXXFLAGS			:= -Wall -Wextra -Werror
DEBUG				:= -g
OBJECTS				:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))
INCLUDES			:= -I./$(PATH_INC)
LIBFT				:= libft/libft.a
INC_LIBFT			:= -I libft/includes
# MLX					:= minilibx_macos/libmlx.a
MLX					:= -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -g
# INC_MLX				:= -I minilibx_macos/
INC_MLX				:= -I /usr/X11/include


all: build $(NAME)

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJECTS) 
	$(CXX) -o $@ $(OBJECTS) $(DEBUG) $(CXXFLAGS) $(LIBFT) $(MLX)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CXX) -c -o $@ $(CXXFLAGS) $^ $(DEBUG) $(INCLUDES) $(INC_LIBFT) $(INC_MLX)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re