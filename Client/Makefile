# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/24 17:56:41 by tbalea            #+#    #+#              #
#    Updated: 2015/05/24 18:02:14 by tbalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client

SRC = create_client.c\
	  client.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -g -Wall -Werror -Wextra -c $< -o $@ -I ../Libft

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
