# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2016/11/25 11:46:17 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
CFLAGS = -Wall -Werror -Wextra -g
CPATH = src/
OPATH = obj/
HPATH = inc/ libft/
INC = $(addprefix -I , $(HPATH))
CFILES = main.c\
		 	libstrstr.c\
			get_next_line.c\
			getbin.c\
			builtin.c\
			libenv.c\
			argv.c\
			ft_cd.c\
			prompt.c\
			ft_setenv.c\
			argvtest.c\
			ft_echo.c\
			ft_shlvl.c\
			ft_redirect.c\
			ft_checklink.c\
			hashtable.c\
			hashtable_init.c\
			ft_signal.c\
			init_env.c\
			upper.c\
			init_shell.c

OFILES = $(CFILES:.c=.o)
HFILES = inc/minishell.h libft/libft.h
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft
		$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

debug: $(OBJ)
		make -C libft
		$(CC) -g  $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
		mkdir -p $(OPATH)
		$(CC) $(CFLAGS) $(INC) $< -c -o $@


clean:
		make -C libft clean
		rm -f $(OBJ)

fclean: clean
		make -C libft fclean
		rm -f $(NAME)

re: fclean all
