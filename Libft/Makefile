# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/24 17:45:35 by tbalea            #+#    #+#              #
#    Updated: 2015/05/26 18:42:42 by tbalea           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc

SRC			=	ft_atoi.c\
				ft_isdigit.c\
				ft_putstr.c\
				ft_putendl.c

DSRC		=	./src

DOBJ		=	./obj

INC			=	./include

OBJ			=	$(addprefix $(DOBJ)/, $(addsuffix .o, $(NOM)))

NOM			=	$(basename $(notdir $(SRC)))

FLAG		=	-Wall -Wextra -Werror

all			:	$(NAME)

mkdir		:
	@test -d $(DOBJ) || mkdir $(DOBJ)

$(NAME)		:	mkdir $(OBJ)
	@echo "\033[0;32m> Compiled\033[0m"
	@ar rc $(NAME) $(OBJ)
	@echo "\033[0;31m> Lib created\033[0m"
	@ranlib $(NAME)
	@echo "\033[0;33m> Lib index added\033[0m"

$(DOBJ)/%.o	:	$(DSRC)/%.c
	@$(CC) $(FLAG) -I $(INC) -c -o $@ $< \
		&& echo "\033[1;30m[CC] : Compiled $(notdir $<) \
		[\033[0;32mOk\033[1;30m]\033[0m" \
		|| echo "\033[1;30m[CC] : Compiled $(notdir $<) \
		[\033[0;7;31mError\033[0;1;30m]\033[0m"

clean		:
	@rm -f $(OBJ)
	@rm -rf $(DOBJ)
	@echo "\033[0;34m> Directory cleaned\033[0m"

fclean		:	clean
	@rm -f $(NAME)
	@echo "\033[0;35m> Library removed\033[0m"

re			:	fclean all
