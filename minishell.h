/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:29:35 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/17 11:18:36 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>  
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
#include <termios.h>

# define BUFF_SIZE 1024
# define PROMPT "\033[34m[minishell]~> \033[0m"
# define ERROR -1
# define SUCCESS 0

typedef enum e_token
{
	WORD,
	WHITE_SPACE,
	TO_EXPAND,
	PIPE_LINE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	NEW_LINE,
}	t_token;

typedef struct s_tok_node
{
	char			*content;
	int				len;
	t_token			type;
	struct s_tok_node	*next;
}	t_tok_node;

typedef struct s_tokenze
{
	t_tok_node	*head;
	t_tok_node	*tail;
	int			size;
}	t_tokenze;

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exec_node
{
	char			**cmd;
	char			**redir;
	struct s_exec_node	*next;
}	t_exec_node;

typedef struct s_exec_list
{
	t_exec_node	*head;
	t_exec_node	*tail;
}	t_exec_list;


typedef struct s_temp_files 
{
    char *filename;
    struct s_temp_files *next;
}	t_temp_files;

typedef struct s_prog
{
	char		*r_line;
	int			tokens_len;
	char		*cmd_line;
	char		*tmp;
	t_tokenze	*list_tok;
	t_env		*env_list;
	t_env		*secret_env;
	t_exec_list	*exec_list;
	int			nbr_cmd;
	int			nbr_redir;
	int			nbr_pipe;
	int			i;
	int			j;
	int			pid;
	int			end[2];
	char		*line;
	char		*path;
	char		**all_paths;
	char		*access_path;
	bool		is_env_cmd;
	int			heredoc_fd;
	int			fd_in;
	int			fd_out;
	int			original_stdin;
	int			original_heredoc;
	int			original_stdout;
	int			g_exit_status;
	bool		concatanate;
	int			to_restart_stdin;
	int			prev_pipe[2];
	int			curr_pipe[2];
	bool		is_first;
	bool		is_last;
	char		**env_variables;
	char		*expanded_var;
	bool		is_valid;
	int			dot_count;
	bool		has_non_dot_or_slash;
	t_tokenze	*new_tok_list;
	t_temp_files *temp_files;
	char	*filename;
}	t_prog;

typedef struct s_lexer_state
{
	char	*cmd_line;
	char	*start;
	int		len;
	bool	in_quotes;
	char	current_quote;
}	t_lexer_state;

char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c, t_prog *p);
char		*ft_strndup(const char *str, int len);
void		ft_lstadd_back(t_env **lst, t_env *new);
t_env		*ft_lstnew(char *key, char *value);
int			ft_lstsize(t_env *lst);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strcat(char *restrict s1, const char *restrict s2);
void		*ft_realloc(void *ptr, size_t original_size, size_t new_size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strrchr(const char *s, int c);
char		*ft_strncpy(char *dst, const char *src, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_itoa(int n);
char		*ft_trim(char *str);
void		error_msg(char *msg);
void		error_msg2(char *msg, char *arg);
bool		is_whait_spaces(char c);
bool		is_str_spaces(char *line);
t_tokenze	*init_token_list(t_prog *p);
void		append_node(t_prog *p, char *content, int len, t_token type);
bool		is_operator(char c);
bool		is_quote(char c);
void		*safe_allocation(size_t size, size_t lenght);
// =================== start parssing part ======================
bool		parssing(t_prog *p);
int			count_orignal_space(char *input, int *index);
char		*process_spaces(char *input, int *i, int j);
void		process_characters(t_prog *p, int len, char *quote);
void		lexer(t_prog *p);
void		free_tok_list(t_tokenze *list);
bool		parser(t_prog *p);
void		free_double_ptr(char **str);
void		free_exec_list(t_exec_list *exec_list);
t_exec_list	*init_exec_list(t_prog *p);
void		append_exec_list(t_prog *p, int index, t_exec_list *exec_list);
void		append_exec(t_exec_list *list, t_exec_node *new_node);
void		free_env_list(t_env *list);
void		ft_free_lists(t_prog *prog, char *state);
// =================== end parssing part =========================

// =================== start lexer part ==========================
void		tokenize_word(int *len, char *line, t_prog *p, char *type);
void		init_lexer_state(t_lexer_state *state, t_prog *p);
// =================== end lexer part ===========================

// =================== start expanding part =====================
bool		expand(t_tokenze *list, t_env *env_list, t_prog *p);
bool		is_env_var(char *content);
char		*remove_qoutes(char *content, t_prog *p);
char		*get_env_value(const char *var_name, t_env *env_list);
char		*extract_var_name(const char **start);
char		*append_value(char *res, const char *value, size_t *res_size);
char		*append_char(char *res, char c, size_t *res_size);
char		*replace(char *str, t_env *env_list);
bool		check_var_exist(char *str, t_env **env);
char		*extract_var_name(const char **start);
bool		to_expand(char *content, t_token type);
bool		should_expand(const char*command);
char		*get_env_val(char *str, t_env *env_list);
void		append_new_token_list(t_prog *p, char *content, \
			int len, t_token type);
char *handle_variable(const char **start, t_env *env_list,
                char *result, size_t *result_size);
char *process_string(const char *start, t_env *env_list,
                            char *result, size_t *result_size);
bool		is_ambiguous(const char *filename);
// =================== end expanding part =======================

bool		store_env(char **env, t_prog *p);
bool		store_secret_env(char **env, t_prog *p);
void		free_envirement(t_prog *p);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);

// =================== start builtins part ======================
int			get_args_nbr(char **args);
void		echo(char **args);
void		cd(char **args, t_env *env);
void		pwd(void);
void		env(t_env *env);
void		ft_export(char **args, t_prog *p);
void		ft_exit(char **args);
void		ft_unset(char **args, t_env **env, t_env **s_env);
int			is_in_env(t_env *env, const char *key);
void		env_add(char *new_var, t_env *env);
bool		is_valid_identifier(char *key);
bool		is_special_char(char *str);
void		split_val(char *arg, char **key, char **value);
bool		contain_space(char *str);
char		*ft_copy(char *src, size_t start, size_t end);
// =================== end builtins part =========================

// =================== start execution part ======================
void		execution(t_prog *p, t_exec_list *list);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_found_newline(char *str);
bool		exec_cmds(t_prog *path, t_exec_list *exec_list, t_env *env_list);
char		**convert_env_list(t_env *env_list);
bool		execute_command(char **redirs, char **cmds, t_prog *p);
void		exec_builtin_parent(char **cmd, char **redirs, t_prog *p);
void		close_pipes(t_prog *p);
void		execute(char **cmd, t_prog *p);
void		redirect_output(char *file, int flags);
void		redirect_input(char *file, int flags);
void		check_redirects(char **redirs);
char		*check_path(char **paths, char *cmd);
bool		check_is_builtin(char **type, int *index);
void		exec_builtins(char **cmd, t_prog *p);
void		ft_heredoc(t_prog *p);
void		unlink_temp_files(t_temp_files *temp_files_list);
void		append_temp_file(t_temp_files **lst, t_temp_files *new);
void		*add_temp_file(char *filename, t_prog *p);
void		ft_sign(void);
void		sig_here_doc(t_prog *p);
void		free_envirement(t_prog *p);
// =================== end execution part ======================
#endif
