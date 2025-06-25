/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_%.123456789#_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:38:23 by vtian             #+#    #+#             */
/*   Updated: 2025/06/14 18:33:12 by vtian            ###   ########.fr       */
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

unsigned int	read_int(const UCHAR_T **f)
{
	unsigned int	n;

	n = 0;
	while (ft_isdigit(**f))
	{
		n *= 10;
		n += **f - '0';
		++*f;
	}
	return (n);
}

void	spec_raw_digit(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)s;
	(void)ap;
	if (*table == STEP_FLAGS_WIDTH_PRECISION_FORMAT)
	{
		state->spec->width = read_int(&state->f);
		*table = STEP_PRECISION_FORMAT;
	}
	else if (*table == STEP_PRECISION_FORMAT)
	{
		state->spec->prec = read_int(&state->f);
		*table = STEP_FORMAT;
	}
	else
	{
		state->err = 1;
		*table = NONE;
	}
}

void	spec_precision(FILE *s, va_list ap, t_state *state,
	t_dispatch_step *table)
{
	(void)s;
	(void)ap;
	if (*table == STEP_FLAGS_WIDTH_PRECISION_FORMAT
		|| *table == STEP_PRECISION_FORMAT)
	{
		*table = STEP_PRECISION_FORMAT;
		++(state->f);
	}
	else
	{
		state->err = 1;
		*table = NONE;
	}
}

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
