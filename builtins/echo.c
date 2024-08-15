/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:35:26 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 21:31:52 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

static bool	parse_echo(char **args, int *i)
{
	bool	option;
	char	*p;

	option = false;
	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		p = args[*i] + 1;
		while (*p == 'n')
			p++;
		if (*p == '\0')
		{
			option = true;
			(*i)++;
		}
		else
			break ;
	}
	return (option);
}

static void	print_echo_args(char **args, int i, bool option_n)
{
	bool	first;

	first = true;
	while (args[i])
	{
		if (!first)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		first = false;
		i++;
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	echo(char **args)
{
	int		i;
	bool	option;

	i = 1;
	option = parse_echo(args, &i);
	print_echo_args(args, i, option);
	g_exit_status = 0;
}
