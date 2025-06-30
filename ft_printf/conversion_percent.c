/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:02:52 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:02:53 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "ft_printf_internal_bonus.h"
#include "libft.h"

void	spec_conversion_percent(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)ap;
	(void)state;
	outstring(s, &state->done, "%%", 1);
	*table = NONE;
}
