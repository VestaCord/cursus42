/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:53:58 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:29:28 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

// sets buf to n 0x value in string form
void	ft_set_ptoa(UCHAR_T *buf, void *p)
{
	int					i;
	unsigned long long	n;
	const UCHAR_T		*hex_base = (UCHAR_T *)"0123456789abcdef";

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
	UCHAR_T	str[15];
	void	*p;

	p = (void *)va_arg(ap, void *);
	ft_strlcpy((CHAR_T *)str, "0x", 3);
	ft_set_ptoa(str + 2, p);
	if (!state->spec->left)
		pad(s, state, str, state->spec->width);
	outstring(s, &state->done, (CHAR_T *)str, ft_strlen((char *)str));
	if (state->spec->left)
		pad(s, state, str, state->spec->width);
	*table = NONE;
}
