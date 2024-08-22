#include "minishell.h"


bool	exist(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}



char	*remove_qoutes(char *content, t_prog *p)
{
	char		*str;
	char		count;
	int			i;
	size_t		j;

	str = malloc(ft_strlen(content) + 1);
	if (!str)
		(free(content), ft_free_lists(p, "exit"));
	i = 0;
	j = 0;
	count = 0;
	//printf("[%s]\n", content); //"'"'"l's""
	while (content[i])
	{
		if ((content[i] == '"' || content[i] == '\'') && count == 0 && exist(content + i + 1, content[i]))
			count = content[i];
		else if (content[i] == count)
			count = 0;
		else
			str[j++] = content[i];//'
		i++;
	}
	str[j] = '\0';
	return (ft_realloc(str, ft_strlen(content), j));
}
