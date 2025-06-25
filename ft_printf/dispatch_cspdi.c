/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_cspdi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:42 by vtian             #+#    #+#             */
/*   Updated: 2025/06/14 18:49:35 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

void	spec_conversion_char(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	UCHAR_T	c[2];

	ft_memset(c, 0, 2);
	*c = (unsigned char)va_arg(ap, int);
	if (!state->spec->left)
		pad(s, state, c, state->spec->width);
	outstring(s, &state->done, (CHAR_T *)c, 1);
	if (state->spec->left)
		pad(s, state, c, state->spec->width);
	*table = NONE;
}

void	spec_conversion_string(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	UCHAR_T	*str;

	str = (unsigned char *)va_arg(ap, char *);
	if (state->spec->width && state->spec->prec != -1)
		state->spec->width += (ft_strlen((CHAR_T *)str) - state->spec->prec);
	if (!state->spec->left)
		pad(s, state, str, state->spec->width);
	if (state->spec->prec != -1
		&& (size_t)state->spec->prec < ft_strlen((char *)str))
		outstring(s, &state->done, (CHAR_T *)str, state->spec->prec);
	else
		outstring(s, &state->done, (CHAR_T *)str, ft_strlen((char *)str));
	if (state->spec->left)
		pad(s, state, str, state->spec->width);
	*table = NONE;
}

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

// currently pad also not working anyway?
void	spec_conversion_int(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	UCHAR_T	*str;
	int		n;
	int		width;

	n = va_arg(ap, int);
	str = (UCHAR_T *)ft_itoa(n);
	width = state->spec->width - (n >= 0 && (state->spec->showsign
				|| state->spec->space)) + (!state->spec->prec && !n);
	if (state->spec->prec > (int)ft_strlen((CHAR_T *)str))
		width -= state->spec->prec - ft_strlen((CHAR_T *)str);
	if (!state->spec->left)
		pad(s, state, str, width);
	if (n >= 0 && state->spec->showsign)
		outstring(s, &state->done, "+", 1);
	else if (n >= 0 && state->spec->space)
		outstring(s, &state->done, " ", 1);
	if (state->spec->prec != -1)
		pad_zero(s, state, str, (state->spec->prec));
	if (!state->spec->prec && *str == '0' && str[1] == '\0')
		*str = '\0';
	outstring(s, &state->done, (CHAR_T *)str, ft_strlen((char *)str));
	if (state->spec->left)
		pad(s, state, str, width);
	free(str);
	*table = NONE;
}
