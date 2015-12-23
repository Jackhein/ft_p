# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/24 17:56:41 by tbalea            #+#    #+#              #
#    Updated: 2015/05/26 18:58:25 by tbalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = serveur

SRC = create_server.c\
	  server.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -g -Wall -Werror -Wextra -c $< -o $@ -I ../Libft/

makefile_fclean:
	make -C ../Libft/ fclean

$(NAME): $(OBJ)
	make -C ../Libft
	gcc -g -o $(NAME) $(OBJ) -L ../Libft

clean: makefile_fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
