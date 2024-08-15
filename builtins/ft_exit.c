/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:34:48 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/14 21:43:33 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

long int	modulo(long int nbr)
{
	long int	result;

	result = nbr % 256;
	if (result < 0)
		result += 256;
	return (result);
}

static int	check_overflow(char *nbr)
{
	size_t	len;
	int		res;

	len = ft_strlen(nbr);
	res = (nbr[len - 3] - '0') * 100 + (nbr[len - 2] - '0')
		* 10 + (nbr[len - 1] - '0');
	if ((nbr[0] != '-' && len == 19 && res > 807)
		|| (len > 19 && nbr[0] != '-'))
		return (1);
	if ((nbr[0] == '-' && len == 20 && res > 808) || len > 20)
		return (1);
	return (0);
}

static long int	ft_atoi(char *nb)
{
	long int	result;
	size_t		i;
	bool		flag;
	int			sign;
	char		*nbr;

	i = 0;
	result = 0;
	flag = true;
	sign = 1;
	nbr = ft_trim(nb);
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i])
	{
		flag = false;
		if (ft_isdigit(nbr[i]))
			result = result * 10 + nbr[i] - '0';
		if (check_overflow(nbr) || !ft_isdigit(nbr[i]))
			return -1;
		i++;
	}
	result *= sign;
	if (flag)
		return -1;
	return (modulo(result));
}

static size_t	count_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	ft_exit(char **args)
{
	size_t		args_len;
	long int	num;

	args_len = count_args(args);
	num = -3;
	if (args_len >= 2)
		num = ft_atoi(args[1]);
	else
		exit(g_exit_status);
	if (args_len > 2 && num != -1)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return ;
	}
	else if (num == -1)
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		g_exit_status = 2;
		exit(2);
	}
	exit(num);
}
