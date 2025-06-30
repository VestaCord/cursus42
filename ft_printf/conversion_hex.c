/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:16:50 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:57:06 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

void	ft_strupper(unsigned char *s)
{
	while (*s)
	{
		*s = ft_toupper(*s);
		s++;
	}
}

void	spec_conversion_hex(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	UCHAR_T				*str;
	int					width;

	str = (unsigned char *)ft_utoa(va_arg(ap, unsigned long long), 16);
	width = state->spec->width - 2 * (state->spec->alt)
		+ (!state->spec->prec && !ft_strncmp((CHAR_T *)str, "0", 2));
	if (state->spec->prec > (int)ft_strlen((CHAR_T *)str))
		width -= state->spec->prec - ft_strlen((CHAR_T *)str);
	if (!state->spec->left)
		pad(s, state, str, width);
	if ((state->spec->alt) && *state->f == 'X')
		outstring(s, &state->done, "0X", 2);
	else if ((state->spec->alt) && *state->f == 'x')
		outstring(s, &state->done, "0x", 2);
	if (*state->f == 'X')
		ft_strupper(str);
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
