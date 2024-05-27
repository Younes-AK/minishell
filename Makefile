# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 11:16:08 by yakazdao          #+#    #+#              #
#    Updated: 2024/05/27 10:14:04 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
Flags = -Wall -Werror -Wextra

NAME = minishell
RM = rm -rf
MAND_SRC =  main.c \
			functions/ft_split.c \
			functions/ft_strlen.c \
			functions/ft_strjoin.c \
			functions/ft_strdup.c \
			functions/ft_strndup.c \
			functions/ft_strcmp.c \
			functions/ft_strchr.c \
			functions/ft_substr.c \
		 	minishell_utils/errors_free.c \
		 	minishell_utils/help_func.c \
			parssing.c lexer.c \
		 	minishell_utils/help_func2.c
			
MAND_OBJ = $(MAND_SRC:.c=.o)

$(NAME): $(MAND_OBJ)
	$(CC) $(MAND_OBJ) -lreadline -o $(NAME) 
	@echo "✅ Done"

all: $(NAME) 
%.o : %.c minishell.h
	${CC} ${Flags} -c -o $@ $<

clean:
	$(RM) $(MAND_OBJ)
fclean: clean
	$(RM) $(NAME) 
	@echo "🧹 Cleaning up..."
	@echo "✅ Done"
re:	fclean all