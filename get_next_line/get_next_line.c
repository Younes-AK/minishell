/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:11:14 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/11 10:59:22 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_free(char *str, char *buff)
{
	char	*line;

	if (!buff)
		return (NULL);
	line = ft_strjoin2(str, buff);
	if (!line)
		return (free(str), NULL);
	return (line);
}

char	*ft_get_rest(char *str)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	rest = (char *)malloc(ft_strlen(str) - i + 1);
	if (!rest)
		return (NULL);
	j = 0;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	return (free(str), rest);
}

char	*ft_get_one_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_reader(char *buff, int fd)
{
	char	*line;
	ssize_t	r_byte;

	r_byte = 1;
	line = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!line)
		return (free(buff), NULL);
	while (!(ft_found_newline(buff)) && r_byte != 0)
	{
		r_byte = read(fd, line, BUFFER_SIZE);
		if (r_byte == -1)
		{
			free(line);
			free(buff);
			return (NULL);
		}
		line[r_byte] = 0;
		buff = ft_join_free(buff, line);
	}
	free(line);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_reader(buffer, fd);
	if (!buffer)
		return (NULL);
	line = ft_get_one_line(buffer);
	buffer = ft_get_rest(buffer);
	return (line);
}
