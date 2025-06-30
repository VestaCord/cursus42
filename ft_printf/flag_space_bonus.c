/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_-0+_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:23:37 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:00:29 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"

void	spec_flag_space(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)s;
	(void)ap;
	if (*table == STEP_FLAGS_WIDTH_PRECISION_FORMAT)
	{
		if (!state->spec->showsign)
			state->spec->space = 1;
		++(state->f);
	}
	else
	{
		state->err = 1;
		*table = NONE;
	}
}
