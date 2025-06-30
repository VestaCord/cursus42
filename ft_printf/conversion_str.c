/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:52:13 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:52:58 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

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
