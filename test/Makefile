# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/26 19:02:12 by tbalea            #+#    #+#              #
#    Updated: 2015/12/30 21:57:28 by tbalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_p

CLT = client.c\
	  client_error.c\
	  client_spec_cmd.c\
	  client_rcv.c\
	  create_client.c\

SER = create_server.c\
	  server_cd.c\
	  server_ls.c\
	  server_cmd.c\
	  server_error.c\
	  server_pwd.c\
	  server.c\

SRC = ft_atoi.c\
	  ft_itoa.c\
	  ft_bzero.c\
	  ft_isempty.c\
	  ft_isdigit.c\
	  ft_strlen.c\
	  ft_strcmp.c\
	  ft_strdelvoid.c\
	  ft_strncmp.c\
	  ft_strnew.c\
	  ft_strsplit.c\
	  ft_strtrim.c\
	  ft_memalloc.c\
	  ft_memchr.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memset.c\
	  ft_putchar.c\
	  ft_putstr.c\
	  ft_putendl.c\
	  ft_resizestr.c\
	  get_next_line.c\

FLG = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME):
	gcc $(FLG) $(SRC) $(CLT) -o client
	gcc $(FLG) $(SRC) $(SER) -o serveur

fclean:
	rm -f client serveur

re: fclean all
