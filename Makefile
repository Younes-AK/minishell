# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 18:04:20 by yakazdao          #+#    #+#              #
#    Updated: 2024/06/01 17:10:17 by yakazdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC = cc
# FLAGS = -Wall -Werror -Wextra -g -fsanitaize=address
# NAME = minishell
# RM = rm -rf

# COLOR_RESET   = \033[0m
# COLOR_RED     = \033[31m
# COLOR_GREEN   = \033[32m
# COLOR_YELLOW  = \033[33m
# COLOR_BOLD    = \033[1m

# MAND_SRC = main.c \
#             functions/ft_split.c \
#             functions/ft_strlen.c \
#             functions/ft_strjoin.c \
#             functions/ft_strdup.c \
#             functions/ft_strndup.c \
#             functions/ft_strcmp.c \
#             functions/ft_strchr.c \
#             functions/ft_substr.c \
#             functions/ft_lstadd_back.c \
#             functions/ft_lstnew.c \
#             minishell_utils/errors_free.c \
#             minishell_utils/help_func.c \
#             parssing.c lexer.c parser.c \
#             minishell_utils/help_func2.c \
#             expand.c 
            
# MAND_OBJ = $(MAND_SRC:.c=.o)

# $(NAME): $(MAND_OBJ)
# 	@echo "$(COLOR_YELLOW)Compiling... Please wait.$(COLOR_RESET)"
# 	@$(CC) $(MAND_OBJ) -lreadline -o $(NAME)
# 	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

# all: $(NAME)

# %.o: %.c minishell.h
# 	@$(CC) $(FLAGS) -c -o $@ $<

# clean:
# 	@echo "$(COLOR_RED)🧹 Cleaning object files...$(COLOR_RESET)"
# 	@$(RM) $(MAND_OBJ)

# fclean: clean
# 	@echo "$(COLOR_RED)🧹 Cleaning executable...$(COLOR_RESET)"
# 	@$(RM) $(NAME)
# 	@echo "$(COLOR_GREEN)✅ Done$(COLOR_RESET)"

# re: fclean all

# .PHONY: all clean fclean re


CC = cc

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

FILE =  main.c \
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
            minishell_utils/help_func2.c \
            expand.c 

OBJECT_FILE = $(FILE:.c=.o)

NAME = minishell

READLINE_INC = -I$(shell brew --prefix readline)/include

READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

all : $(NAME)

$(NAME) : $(OBJECT_FILE)
	$(CC) $(FLAGS) $(READLINE_LIB) $(OBJECT_FILE) -o $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

%.o : %.c minishell.h
	@echo "\033[0;34mCompiling $< .\033[0;m"
	$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

clean :
	@echo "\033[0;31mRemoving object files.\033[0;m"
	rm -f $(OBJECT_FILE)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

re : fclean all

fclean : clean
	@echo "\033[0;31mRemoving executable file.\033[0;m"
	rm -f $(NAME)
	@echo "\033[1;32mFClean DONE ✅\033[0;m"

.PHONY : clean
