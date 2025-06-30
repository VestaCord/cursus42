/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:49:42 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:58:46 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

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
