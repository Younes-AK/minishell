#include "minishell.h"

char	*remove_quotes(char *content, t_prog *p)
{
	char		*str;
	char		count;
	int			i;
	size_t		j;

	str = malloc(ft_strlen(content));
	if (!str)
		(free(content), ft_free_lists(p, "exit"));
	i = 0;
	j = 0;
	count = 0;
	printf("[%s]\n", content);
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
			count = content[i];
		else if (content[i] == count)
			count = 0;
		else
			str[j++] = content[i];
		i++;
	}
	str[j] = '\0';
	return (ft_realloc(str, ft_strlen(content), j));
}
