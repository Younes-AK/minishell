# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 18:04:20 by yakazdao          #+#    #+#              #
#    Updated: 2024/07/07 14:28:34 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Werror -Wextra -g #-fsanitize=address
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
            minishell_utils/errors_free.c \
            minishell_utils/help_func.c \
            parssing/parssing.c \
            parssing/parssing_utils.c \
            parssing/create_exec_list.c \
            parssing/lexer.c  parssing/parser.c \
            minishell_utils/help_func2.c \
            minishell_utils/help_func3.c \
            expand/expand.c expand/expand_utils.c \
            builtins/echo.c  builtins/cd.c \
            builtins/pwd.c builtins/env.c \
            builtins/ft_export.c builtins/ft_unset.c \
            execution/execution.c \
            execution/exec_cmds.c \
            execution/execution_utils.c \
            get_next_line/get_next_line.c \
            get_next_line/get_next_line_utils.c

MAND_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(MAND_SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MAND_OBJ)
	@echo "Compiling... Please wait."
	@$(CC) $(CFLAGS) $(MAND_OBJ) -lreadline -o $(NAME)
	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c minishell.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "🧹 Cleaning executable..."
	@$(RM) $(NAME)
	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

re: fclean all




# CC = cc

# FLAGS = #-Wall -Wextra -Werror -g -fsanitize=address

# FILE =  main.c \
#             functions/ft_split.c \
#             functions/ft_strlen.c \
#             functions/ft_strjoin.c \
#             functions/ft_strdup.c \
#             functions/ft_strndup.c \
#             functions/ft_strcmp.c \
#             functions/ft_strchr.c \
#             functions/ft_strrchr.c \
#             functions/ft_substr.c \
#             functions/ft_lstadd_back.c \
#             functions/ft_lstnew.c \
#             functions/ft_lstsize.c \
#             functions/ft_memcpy.c \
#             functions/ft_strcat.c \
#             functions/ft_realloc.c \
#             functions/ft_isalnum.c \
#             functions/ft_isalpha.c \
#             functions/ft_isdigit.c \
#             functions/ft_putendl_fd.c \
#             functions/ft_putstr_fd.c \
#             functions/ft_putchar_fd.c \
#             functions/ft_strcpy.c \
#             functions/ft_strncpy.c \
#             minishell_utils/errors_free.c \
#             minishell_utils/help_func.c \
#             parssing.c lexer.c parser.c \
#             minishell_utils/help_func2.c \
#             minishell_utils/help_func3.c \
#             expand.c expand_utils.c \
#             builtins/echo.c \
#             builtins/cd.c builtins/pwd.c \
#             builtins/env.c builtins/ft_export.c

# OBJECT_FILE = $(FILE:.c=.o)

# NAME = minishell

# READLINE_INC = -I$(shell brew --prefix readline)/include

# READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

# all : $(NAME)

# $(NAME) : $(OBJECT_FILE)
# 	$(CC) $(FLAGS) $(READLINE_LIB) $(OBJECT_FILE) -o $(NAME)
# 	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

# %.o : %.c minishell.h
# 	@echo "\033[0;34mCompiling $< .\033[0;m"
# 	$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

# clean :
# 	@echo "\033[0;31mRemoving object files.\033[0;m"
# 	rm -f $(OBJECT_FILE)
# 	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

# re : fclean all

# fclean : clean
# 	@echo "\033[0;31mRemoving executable file.\033[0;m"
# 	rm -f $(NAME)
# 	@echo "\033[1;32mFClean DONE ✅\033[0;m"

# .PHONY : clean
