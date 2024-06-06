/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/06/01 15:29:16 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
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
    ENV,
    PIPE_LINE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_HEREDOC,
    REDIR_APPEND,
	
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    ESCAPE,
    NEW_LINE,
}	t_token;

typedef struct s_tok_node
{
    char *content;
    int len;
    t_token type;
    struct s_tok_node *next;
} t_tok_node;

typedef struct s_tokenze 
{
    t_tok_node *head;
    t_tok_node *tail;
    int size;
} t_tokenze;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_exec_node
{
	char **cmd;
	char **redir;
	struct s_exec_node *next;
}	t_exec_node;

typedef struct s_exec_list
{
    t_exec_node *head;
    t_exec_node *tail;
} t_exec_list;


typedef struct s_prog
{
	char		*r_line;
	int			tokens_len;
	char 		*cmd_line;
	char		*d;
	t_tokenze	*list_tok;
	t_env		*env_list;
	t_exec_list	*exec_list;
	
	int nbr_cmd;
	int nbr_redir;
	int nbr_pipe;
}	t_prog;

 

char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
char	 	*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strndup(const char *str, int len);
void		ft_lstadd_back(t_env **lst, t_env *new);
t_env		*ft_lstnew(char *key, char *value);

void		error_msg(char *msg);
bool		is_whait_spaces(char c);
bool		is_str_spaces(char *line);
t_tokenze 	*init_list();

void		append_node(t_tokenze *list, char *content, int len, t_token type);
bool		is_operator(char c);
bool		is_quote(char c);

void		*safe_allocation(size_t size, size_t lenght);
bool		parssing(t_prog *p);
void		lexer(t_prog *p, t_tokenze *list);
void		free_list(t_tokenze *list);
void		_init(int ac, char **av, char **env);
bool		parser(t_prog *p, char **env, t_exec_list *exec_list);
void		free_double_ptr(char **str);
void        free_exec_list(t_exec_list *exec_list);

t_exec_list *init_exec_list();
void        append_exec(t_exec_list *list, t_exec_node *new_node);
void        free_env_list(t_env *list) ;
void        expand(t_tokenze *list, t_env *env_list);
#endif