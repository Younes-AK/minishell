/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:57:04 by yakazdao          #+#    #+#             */
/*   Updated: 2024/08/22 19:29:44 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_num(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		num;
	char	*str;
	long	nbr;

	1 && (nbr = n, num = ft_num(nbr), str = malloc(num + 1));
	if (!str)
		return (NULL);
	if (nbr == 0)
	{
		*str = '0';
		str[1] = '\0';
		return (str);
	}
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	str[num] = '\0';
	while (nbr > 0)
	{
		str[--num] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (str);
}
