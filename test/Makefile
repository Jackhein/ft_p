# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/26 19:02:12 by tbalea            #+#    #+#              #
#    Updated: 2016/01/13 06:32:33 by tbalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_p

TRF = transfer_get.c\
	  transfer_put.c\
	  transfer_crypt.c\

CLT = client.c\
	  client_error.c\
	  client_spec_cmd.c\
	  client_rcv.c\
	  client_create.c\

SER = server_create.c\
	  server_cd.c\
	  server_ls.c\
	  server_cmd.c\
	  server_epur_access_arg.c\
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
	  ft_strdelelem.c\
	  ft_strdelvoid.c\
	  ft_strncmp.c\
	  ft_strnew.c\
	  ft_tabjoin.c\
	  ft_strsplit.c\
	  ft_strjoin.c\
	  ft_strcjoin.c\
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
	  ft_tabdel.c\
	  ft_tabdelelem.c\
	  get_next_line.c\
	  ft_strcat.c\
	  ft_strncat.c\
	  ft_strdup.c\

FLG = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME):
	gcc $(FLG) $(SRC) $(CLT) $(TRF) -o client
	gcc $(FLG) $(SRC) $(SER) $(TRF) -o serveur

fclean:
	rm -f client serveur

re: fclean all
