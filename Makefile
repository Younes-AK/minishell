# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 18:04:20 by yakazdao          #+#    #+#              #
#    Updated: 2024/05/30 18:04:34 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SANITIZE_FLAGS = -fsanitize=thread
FLAGS = -Wall -Werror -Wextra $(SANITIZE_FLAGS)
NAME = minishell
RM = rm -rf

# Define ANSI color codes
COLOR_RESET   = \033[0m
COLOR_RED     = \033[31m
COLOR_GREEN   = \033[32m
COLOR_YELLOW  = \033[33m
COLOR_BOLD    = \033[1m

# Source and object files
MAND_SRC = main.c \
            functions/ft_split.c \
            functions/ft_strlen.c \
            functions/ft_strjoin.c \
            functions/ft_strdup.c \
            functions/ft_strndup.c \
            functions/ft_strcmp.c \
            functions/ft_strchr.c \
            functions/ft_substr.c \
            functions/ft_lstadd_back.c \
            functions/ft_lstnew.c \
            minishell_utils/errors_free.c \
            minishell_utils/help_func.c \
            parssing.c lexer.c parser.c \
            minishell_utils/help_func2.c
            
MAND_OBJ = $(MAND_SRC:.c=.o)

$(NAME): $(MAND_OBJ)
	@echo "$(COLOR_YELLOW)Compiling... Please wait.$(COLOR_RESET)"
	@$(CC) $(MAND_OBJ) -lreadline -o $(NAME) $(SANITIZE_FLAGS)
	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

all: $(NAME)

%.o: %.c minishell.h
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@echo "$(COLOR_RED)🧹 Cleaning object files...$(COLOR_RESET)"
	@$(RM) $(MAND_OBJ)

fclean: clean
	@echo "$(COLOR_RED)🧹 Cleaning executable...$(COLOR_RESET)"
	@$(RM) $(NAME)
	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re
