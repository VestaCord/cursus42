/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:20:11 by vtian             #+#    #+#             */
/*   Updated: 2025/07/04 00:12:11 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"
#include "libft.h"

// Inserts padding up to width - strlen(string)
void	pad(FILE *s, t_state *state, unsigned char *string, int width)
{
	if (width > (int)ft_strlen((const char *)string))
	{
		while (width > (int)ft_strlen((const char *)string))
		{
			outstring(s, &state->done, (char *)&state->spec->pad, 1);
			width--;
		}
	}
}

void	pad_zero(FILE *s, t_state *state, unsigned char *string, int width)
{
	state->spec->pad = '0';
	pad(s, state, string, width);
	state->spec->pad = ' ';
}

// NONLIBC [flags][width][.precision]conversion
// designated initializer list for dispatching specifiers
// accessed by specifier  (the smallest ascii escaped)

const t_dispatch_handler	*get_dispatch_table(void)
{
	static const t_dispatch_handler	table[('x' + 1)] = {
	['c'] = spec_conversion_char,
	['s'] = spec_conversion_string,
	['p'] = spec_conversion_pointer,
	['d'] = spec_conversion_int,
	['i'] = spec_conversion_int,
	['u'] = spec_conversion_uint,
	['x'] = spec_conversion_hex,
	['X'] = spec_conversion_hex,
	['%'] = spec_conversion_percent
	};

	return (table);
}

void	dispatch(FILE *s, va_list ap, t_state *state)
{
	t_dispatch_step	table;

	table = STEP_FLAGS_WIDTH_PRECISION_FORMAT;
	while (table != NONE)
	{
		if ((unsigned char)*state->f > 'x'
			|| !get_dispatch_table()[(unsigned char)*state->f])
			state->err = 1;
		else
			(*get_dispatch_table()[(unsigned char)*state->f])
				(s, ap, state, &table);
	}
}
