/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakazdao <yakazdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:37:17 by yakazdao          #+#    #+#             */
/*   Updated: 2024/05/20 11:46:52 by yakazdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char *ft_substr(const char *s, int start, int len)
// {
//     char *substr = (char *)malloc((len + 1) * sizeof(char));
//     if (!substr)
//         return NULL;
//     strncpy(substr, s + start, len);
//     substr[len] = '\0';
//     return substr;
// }

static void free_strings(int count, char **array)
{
    for (int i = 0; i < count; i++)
        free(array[i]);
    free(array);
}

static int is_special_char(char c)
{
    return (c == '|' || c == ';' || c == '<' || c == '>');
}

static int handle_special_char(const char *s, int *j, char **array, int *i)
{
    if (s[*j] == '<' && s[*j + 1] == '<') {
        array[*i] = ft_substr(s, *j, 2);
        (*j)++;
    } else if (s[*j] == '>' && s[*j + 1] == '>') {
        array[*i] = ft_substr(s, *j, 2);
        (*j)++;
    } else {
        array[*i] = ft_substr(s, *j, 1);
    }
    if (!array[*i])
        return 0;
    (*i)++;
    return 1;
}

char **ft_tokenize(const char *s) //       < file | echo "hello world" > outfile
{
    char **array = malloc(256 * sizeof(char *));
    if (!array)
        return NULL;

    int i = 0, j = 0, start = 0, in_single_quote = 0, in_double_quote = 0;
    while (s[j])
    {
        if (s[j] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (s[j] == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (!in_single_quote && !in_double_quote && (s[j] == ' ' || is_special_char(s[j]))) {
            if (j > start) {
                array[i] = ft_substr(s, start, j - start);
                if (!array[i++]) {
                    free_strings(i, array);
                    return NULL;
                }
            }
            if (is_special_char(s[j])) {
                if (!handle_special_char(s, &j, array, &i)) {
                    free_strings(i, array);
                    return NULL;
                }
            }
            start = j + 1;
        }
        j++;
    }
    if (j > start) {
        array[i] = ft_substr(s, start, j - start);
        if (!array[i++]) {
            free_strings(i, array);
            return NULL;
        }
    }
    array[i] = NULL;
    return array;
}