/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:53:58 by vtian             #+#    #+#             */
/*   Updated: 2025/07/07 21:06:18 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

// sets buf to n 0x value in string form
void	ft_set_ptoa(unsigned char *buf, void *p)
{
	int					i;
	unsigned long long	n;
	const unsigned char	*hex_base = (unsigned char *)"0123456789abcdef";

	n = (unsigned long long)p;
	buf[12] = 0;
	i = 12;
	while (i-- > 0)
	{
		if (n > 0)
		{
			buf[i] = hex_base[n % 16];
			n /= 16;
		}
		else
		{
			buf[i] = '0';
		}
	}
}

void	spec_conversion_pointer(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	unsigned char	*str;
	void			*p;
	unsigned char	*tmp;

	p = (void *)va_arg(ap, void *);
	if (p)
	{
		tmp = (unsigned char *)ft_utoa((unsigned long long)p, 16);
		str = (unsigned char *)ft_strjoin("0x", (char *)tmp);
		free (tmp);
	} else {
		str = (unsigned char *)ft_strdup("(nil)");
	}
	if (!state->spec->left)
		pad(s, state, str, state->spec->width);
	outstring(s, &state->done, (char *)str, ft_strlen((char *)str));
	if (state->spec->left)
		pad(s, state, str, state->spec->width);
	free(str);
	*table = NONE;
}
