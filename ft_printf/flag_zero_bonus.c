/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_zero_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:00:07 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:00:08 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"

void	spec_flag_zero_pad(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)s;
	(void)ap;
	if (*table == STEP_FLAGS_WIDTH_PRECISION_FORMAT)
	{
		if (!state->spec->left)
			state->spec->pad = '0';
		++(state->f);
	}
	else if (*table == STEP_PRECISION_FORMAT)
	{
		state->spec->prec = 0;
		++(state->f);
	}
	else
	{
		state->err = 1;
		*table = NONE;
	}
}
