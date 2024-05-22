# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 11:16:08 by yakazdao          #+#    #+#              #
#    Updated: 2024/05/21 13:11:44 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
Flags = -Wall -Werror -Wextra

NAME = minishell
RM = rm -rf
MAND_SRC =  main.c \
			functions/ft_memcmp.c \
			functions/ft_split.c \
			functions/ft_strlen.c \
			functions/ft_strjoin.c \
			functions/ft_strdup.c \
			functions/ft_strlcat.c \
			functions/ft_strlcpy.c \
			functions/ft_strncmp.c \
			functions/ft_strchr.c \
			functions/ft_substr.c \
			functions/ft_lstnew_bonus.c \
			functions/ft_lstadd_back_bonus.c \
			functions/ft_lstclear_bonus.c \
			utils/help_func.c \
			utils/ft_errors_free.c \
			parssing.c utils/tokenization.c
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