/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/22 15:23:49 by yakazdao         ###   ########.fr       */
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
typedef struct s_tokens
{
	char **commands;
	char **redirections;
	struct s_tokens *next;
}	t_tokens;

typedef enum e_operators
{
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	HERE_DOC,
	DREDIR_OUT,
}	t_operators;
 

typedef struct s_prog
{
	char *line_rd;
	char *cmd_line;
	char **patterns;
	char **tokens;
	int	pipe_nbr;

}	t_prog;

int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dest, const char *src, size_t len);
size_t		ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char	 	*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
bool 		is_whaitspace(char c);
bool 		is_operator(char c);
void		parssing(t_prog *p);
void		*allocate(size_t element_size, size_t length);
void 		ft_error(char *msg);
void		tokenization(t_prog *p, t_tokens *t);
char 		**ft_tokenize(const char *s);
void		free_allocation(char **var);
int			get_nbr_words(const char *line, int *pos);
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstnew(void *cmdline ,char *type, int i, int j, int lenght);
#endif