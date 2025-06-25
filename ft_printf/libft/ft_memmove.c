/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:33:39 by vtian             #+#    #+#             */
/*   Updated: 2025/05/22 20:39:55 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
// originally i intended to malloc a tmp but i saw other people
// split into dst > src and dst < src (write from start vs end)
{
	size_t	i;

	if (!dst || !src)
		return (NULL);
	if (dst > src)
	{
		while (len-- > 0)
			*(char *)(dst + len) = *(char *)(src + len);
	}
	else if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dst);
}
