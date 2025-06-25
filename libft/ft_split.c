/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:22:30 by vtian             #+#    #+#             */
/*   Updated: 2025/05/27 22:34:37 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(const char *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

char	*delim_strdup(const char *s, char c)
{
	size_t	i;
	char	*tmp;

	tmp = ft_strdup(s);
	if (!tmp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (tmp[i] == c)
			tmp[i] = 0;
		i++;
	}
	return (tmp);
}

void	free_split(char *tmp, char **strlist)
{
	int	i;

	if (!strlist)
		return ;
	i = 0;
	while (strlist[i])
	{
		free(strlist[i]);
		i++;
	}
	free(strlist);
	if (!tmp)
		return ;
	free(tmp);
}

char	**ft_split(const char *s, char c)
{
	char	**strlist;
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = delim_strdup(s, c);
	strlist = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!strlist || !tmp)
		return (NULL);
	i = -1;
	j = 0;
	while (++i <= ft_strlen(s))
	{
		if (tmp[i] && (i == 0 || !tmp[i - 1]))
		{
			strlist[j] = ft_strdup(tmp + i);
			if (!strlist[j++])
			{
				free_split(tmp, strlist);
				return (NULL);
			}
		}
	}
	free(tmp);
	return (strlist);
}
