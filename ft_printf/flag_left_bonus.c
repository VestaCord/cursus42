/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_left_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:59:32 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:59:33 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"

void	spec_flag_left_align_override(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)s;
	(void)ap;
	if (*table == STEP_FLAGS_WIDTH_PRECISION_FORMAT)
	{
		state->spec->left = 1;
		state->spec->pad = ' ';
		++(state->f);
	}
	else
	{
		state->err = 1;
		*table = NONE;
	}
}
