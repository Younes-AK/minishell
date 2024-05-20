/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/20 16:22:46 by yakazdao         ###   ########.fr       */
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
	char	**tokens;
	int		nbr_tokens;
}	t_tokens;

typedef enum e_token
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
}	t_token;
 

typedef struct s_prog
{
	char *line_rd;
	char *cmd_line;
	char **patterns;
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
void		*allocate(char *type, size_t size);
void 		ft_error(char *msg);
char 		**ft_tokenize(const char *s);

#endif