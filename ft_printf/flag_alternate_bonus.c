/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_alternate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:01:43 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:02:02 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"
#include "libft.h"

void	spec_flag_alt_form(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)s;
	(void)ap;
	if (*table == STEP_FLAGS_WIDTH_PRECISION_FORMAT)
	{
		state->spec->alt = 1;
		++(state->f);
	}
	else
	{
		state->err = 1;
		*table = NONE;
	}
}
