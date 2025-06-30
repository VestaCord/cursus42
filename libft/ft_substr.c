/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:07:14 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:43:04 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
// added case for if start index is out of bounds
{
	size_t	s_len;
	size_t	substring_len;
	char	*new;

	if (NULL == s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substring_len = s_len - start;
	if (len > substring_len)
		len = substring_len;
	new = malloc(len + 1);
	if (NULL == new)
		return (NULL);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}
