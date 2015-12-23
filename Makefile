# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/24 18:06:02 by tbalea            #+#    #+#              #
#    Updated: 2015/05/24 18:45:57 by tbalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_p

all: $(NAME)

$(NAME):
	make -C Libft/
	make -C Server/
	make -C Client/

server:
	make -C Libft/
	make -C Server/

client:
	make -C Libft/
	make -C Client/

clean_client:
	make -C Client/ clean

clean_server:
	make -C Server/ clean

clean_libft:
	make -C Libft/ clean

clean: clean_server clean_client clean_libft

fclean_client:
	make -C Client/ fclean

fclean_server:
	make -C Server/ fclean

fclean_libft:
	make -C Libft/ fclean

fclean: fclean_server fclean_client fclean_libft

re: fclean_all all
