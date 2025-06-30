/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_uint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:57:13 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:57:16 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

// returns digits of n in whatever base
int	ft_digits_base(unsigned int n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_utoa(unsigned int n, int base)
{
	int				len;
	char			*str;

	len = ft_digits_base(n, base);
	str = ft_calloc(len + 1, sizeof(*str));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		if (n % base < 10)
			str[len] = '0' + (n % base);
		else if (n % base < 16)
			str[len] = 'a' - 10 + (n % base);
		n /= base;
	}
	return (str);
}

void	spec_conversion_uint(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	unsigned int	n;
	UCHAR_T			*str;
	int				width;

	n = va_arg(ap, unsigned int);
	str = (unsigned char *)ft_utoa(n, 10);
	width = state->spec->width + (!state->spec->prec && !n);
	if (state->spec->prec > (int)ft_strlen((CHAR_T *)str))
		width -= state->spec->prec - ft_strlen((CHAR_T *)str);
	if (!state->spec->left)
		pad(s, state, str, width);
	state->spec->pad = '0';
	if (state->spec->prec != -1)
		pad(s, state, str, (state->spec->prec));
	state->spec->pad = ' ';
	if (!state->spec->prec && *str == '0' && str[1] == '\0')
		*str = '\0';
	outstring(s, &state->done, (CHAR_T *)str, ft_strlen((char *)str));
	if (state->spec->left)
		pad(s, state, str, width);
	free(str);
	*table = NONE;
}
