/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:55:07 by vtian             #+#    #+#             */
/*   Updated: 2025/05/27 22:02:41 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				is_neg;
	unsigned int	tmp;
	int				len;
	char			*str;

	is_neg = (n < 0);
	tmp = (unsigned int)n;
	if (n < 0)
		tmp = -(unsigned int)n;
	len = ft_digits(tmp) + is_neg;
	str = ft_calloc(len + 1, sizeof(*str));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = '0' + (tmp % 10);
		tmp /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
