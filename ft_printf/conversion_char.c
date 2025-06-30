/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:51:47 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:51:57 by vtian            ###   ########.fr       */
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
