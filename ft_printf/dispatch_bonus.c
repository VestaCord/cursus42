/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:20:11 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:10:32 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"
#include "libft.h"

// Inserts padding up to width - strlen(string)
void	pad(FILE *s, t_state *state, UCHAR_T *string, int width)
{
	if (width > (int)ft_strlen((const char *)string))
	{
		while (width > (int)ft_strlen((const char *)string))
		{
			outstring(s, &state->done, (CHAR_T *)&state->spec->pad, 1);
			width--;
		}
	}
}

void	pad_zero(FILE *s, t_state *state, UCHAR_T *string, int width)
{
	state->spec->pad = '0';
	pad(s, state, string, width);
	state->spec->pad = ' ';
}

// NONLIBC [flags][width][.precision]conversion
// designated initializer list for dispatching specifiers
// accessed by specifier  (the smallest ascii escaped)
static const t_dispatch_handler	g_dispatch_table[('x' + 1)] = {
['c'] = spec_conversion_char,
['s'] = spec_conversion_string,
['p'] = spec_conversion_pointer,
['d'] = spec_conversion_int,
['i'] = spec_conversion_int,
['u'] = spec_conversion_uint,
['x'] = spec_conversion_hex,
['X'] = spec_conversion_hex,
['%'] = spec_conversion_percent,
['-'] = spec_flag_left_align_override,
['0'] = spec_flag_zero_pad,
['.'] = spec_precision,
['#'] = spec_flag_alt_form,
[' '] = spec_flag_space,
['+'] = spec_flag_plus_override,
['1'] = spec_raw_digit,
['2'] = spec_raw_digit,
['3'] = spec_raw_digit,
['4'] = spec_raw_digit,
['5'] = spec_raw_digit,
['6'] = spec_raw_digit,
['7'] = spec_raw_digit,
['8'] = spec_raw_digit,
['9'] = spec_raw_digit
};

void	dispatch(FILE *s, va_list ap, t_state *state)
{
	t_dispatch_step	table;

	table = STEP_FLAGS_WIDTH_PRECISION_FORMAT;
	while (table != NONE)
	{
		if ((unsigned char)*state->f > 'x'
			|| !g_dispatch_table[(unsigned char)*state->f])
			state->err = 1;
		else
			(*g_dispatch_table[(unsigned char)*state->f])(s, ap, state, &table);
	}
}
