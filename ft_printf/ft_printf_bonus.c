/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:25:40 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 23:10:11 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

// Writes string of len to file and write to done
// Sets done -1 if failed to print len
void	outstring(FILE *s, int *done, const CHAR_T *string, int len)
{
	int	i;

	i = 0;
	while (string[i] && i < len)
	{
		write(s->_fileno, string + i, 1);
		i++;
	}
	if (i != len)
		*done = -1;
	else
		*done += len;
}

// Returns char ptr to %specifier
const UCHAR_T	*find_spec(const UCHAR_T *format)
{
	while (*format && *format != '%')
		format++;
	return (format);
}

// Resets format specifier to default values
void	spec_reset(t_spec *spec)
{
	ft_memset(spec, sizeof(t_spec), 0);
	spec->prec = -1;
	spec->pad = ' ';
}

int	ft_vfprintf(FILE *s, const CHAR_T *format, va_list ap)
{
	int		done;
	t_state	*state;

	state = ft_calloc(1, sizeof(t_state));
	state->spec = ft_calloc(1, sizeof(t_spec));
	state->lead_str_end = find_spec((const UCHAR_T *)format);
	state->f = state->lead_str_end;
	outstring(s, &state->done, format,
		state->f - (const UCHAR_T *)format);
	while (*(state->f) && state->done != -1)
	{
		spec_reset(state->spec);
		++(state->f);
		dispatch(s, ap, state);
		++(state->nspecs_done);
		state->end_of_spec = ++(state->f);
		state->f = find_spec(state->end_of_spec);
		outstring(s, &state->done, (CHAR_T *)state->end_of_spec,
			state->f - state->end_of_spec);
	}
	done = state->done;
	free(state->spec);
	free(state);
	return (done);
}

int	ft_printf(char const *str, ...)
// using a tmp ptr in case stdout symbol is banned
{
	va_list	arg;
	FILE	tmp;
	int		done;

	tmp._fileno = STDOUT_FILENO;
	va_start(arg, str);
	done = ft_vfprintf(&tmp, str, arg);
	va_end(arg);
	return (done);
}
