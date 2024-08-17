# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 18:04:20 by yakazdao          #+#    #+#              #
#    Updated: 2024/08/17 11:28:48 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := #-g -fsanitize=address -Wall -Werror -Wextra 
NAME := minishell
RM := rm -rf

COLOR_RESET   := \033[0m
COLOR_GREEN   := \033[32m

SRC_DIR := .
OBJ_DIR := obj

MAND_SRC := main.c \
            functions/ft_split.c \
            functions/ft_strlen.c \
            functions/ft_strjoin.c \
            functions/ft_strjoin_space.c \
            functions/ft_strdup.c \
            functions/ft_strndup.c \
            functions/ft_strcmp.c \
            functions/ft_strchr.c \
            functions/ft_strrchr.c \
            functions/ft_substr.c \
            functions/ft_lstadd_back.c \
            functions/ft_lstnew.c \
            functions/ft_lstsize.c \
            functions/ft_memcpy.c \
            functions/ft_strcat.c \
            functions/ft_realloc.c \
            functions/ft_isalnum.c \
            functions/ft_isalpha.c \
            functions/ft_isdigit.c \
            functions/ft_putendl_fd.c \
            functions/ft_putstr_fd.c \
            functions/ft_putchar_fd.c \
            functions/ft_strcpy.c \
            functions/ft_strncpy.c \
            functions/ft_strncmp.c \
            functions/ft_itoa.c \
            functions/ft_trim.c \
            minishell_utils/errors_free.c \
            minishell_utils/help_func.c \
            minishell_utils/help_func2.c \
            minishell_utils/help_func3.c \
            minishell_utils/help_func4.c \
            parssing/parssing.c \
            parssing/parssing_utils.c \
            parssing/create_exec_list.c \
            parssing/lexer.c  \
            parssing/lexer_utils.c  \
            parssing/parser.c \
            expand/expand.c \
            expand/expand_utils.c \
            expand/expand_utils2.c \
            expand/expand_utils3.c \
            builtins/echo.c  builtins/cd.c \
            builtins/ft_exit.c \
            builtins/builtins_utils.c \
            builtins/pwd.c builtins/env.c \
            builtins/ft_export.c \
            builtins/export_utils.c \
            builtins/ft_unset.c \
            execution/execution.c \
            execution/exec_cmds.c \
            execution/execution_utils.c \
            execution/execution_utils2.c \
            execution/here_doc.c \
            execution/here_doc_utils.c \
            execution/signal.c 

MAND_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(MAND_SRC))

    READLINE_L = ~/.brew/opt/readline/lib
    READLINE_I = ~/.brew/opt/readline/include

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MAND_OBJ)
	@echo "Compiling... Please wait."
	@$(CC) $(CFLAGS) $(MAND_OBJ) -L $(READLINE_L) -lreadline -o $(NAME)
	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c minishell.h

	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -I $(READLINE_I) -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "🧹 Cleaning executable..."
	@$(RM) $(NAME)
	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

re: fclean all

