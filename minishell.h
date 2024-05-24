/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/24 01:27:27 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h> //forb
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

typedef enum e_token {
    WORD,
    WHITE_SPACE,
    NEW_LINE,
    QUOTE,
    DOUBLE_QUOTE,
    ESCAPE,
    ENV,
    PIPE_LINE,
    REDIR_IN,
    REDIR_OUT,
    HERE_DOC,
    DREDIR_OUT,
}	t_token;

typedef enum e_state {
    IN_DQUOTE,
    IN_SQUOTE,
   	DEFAULT,
}	t_state;

typedef struct s_node
{
    char *content;
    int len;
    t_token type;
    t_state state;
    struct s_node *next;
} t_node;
typedef struct s_list {
    t_node *head;
    t_node *tail;
    int size;
} t_list;
 

typedef struct s_prog
{
	char	*r_line;
	char	*start;
	int		tokens_nbr;
	

	char **tokens;

}	t_prog;
 

char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int 		ft_strcmp(const char *str1, const char *str2);
char	 	*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);

void		error_msg(char *msg);
bool		is_whait_spaces(char c);
bool		is_str_spaces(char *line);
t_list 		*init_list();

void		append_element(t_list *list, const char *content, int len, t_token type, t_state state);
bool		is_special_char(char c);
bool		is_quote(char c);
void		tokenize_word(t_list *list, const char *start, int length, t_state state);
void		tokenize_single_char(t_list *list, char c, t_token type, t_state state);
void		tokenize_whitespace(t_list *list, const char *start, int length, t_state state);

void		lexing(t_list *list, const char *input);

#endif