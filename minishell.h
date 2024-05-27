/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/27 15:26:51 by yakazdao         ###   ########.fr       */
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
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ESCAPE,
    ENV,
    PIPE_LINE,
    REDIR_IN,
    REDIR_OUT,
    HERE_DOC,
    DREDIR_OUT,
}	t_token;

typedef struct s_node
{
    char *content;
    int len;
    t_token type;
    struct s_node *next;
} t_node;
typedef struct s_list 
{
    t_node *head;
    t_node *tail;
    int size;
} t_list;
 

typedef struct s_prog
{
	char	*r_line;
	int		tokens_len;
	char 	*cmd_line;
	char *d;
	t_list *list;
	
}	t_prog;
 

char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
char	 	*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strndup(const char *str, int len);

void		error_msg(char *msg);
bool		is_whait_spaces(char c);
bool		is_str_spaces(char *line);
t_list 		*init_list();

void		append_node(t_list *list, char *content, int len, t_token type);
bool		is_operator(char c);
bool		is_quote(char c);
 
void		*safe_allocation(size_t size, size_t lenght);
bool		parssing(t_prog *p);
bool		lexer(t_prog *p, t_list *list);
void		free_list(t_list *list);
void		_init(int ac, char **av, char **env);
#endif