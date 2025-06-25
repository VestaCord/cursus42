/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:27:43 by vtian             #+#    #+#             */
/*   Updated: 2025/06/14 18:38:19 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_BONUS_H
# define FT_PRINTF_INTERNAL_BONUS_H
# include <stdarg.h>
# include <stdio.h>
# include "ft_printf_internal.h"

void	spec_raw_digit(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_precision(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);

// The value should be converted to an "alternate form".  For
// o conversions, the first character of the output string is
// made zero (by prefixing a 0 if it was not zero already).
// For x and X conversions, a nonzero result has the string
// "0x" (or "0X" for X conversions) prepended to it.  For a,
// A, e, E, f, F, g, and G conversions, the result will always
// contain a decimal point, even if no digits follow it
// (normally, a decimal point appears in the results of those
// conversions only if a digit follows).  For g and G
// conversions, trailing zeros are not removed from the result
// as they would otherwise be.  For m, if errno contains a
// valid error code, the output of strerrorname_np(errno) is
// printed; otherwise, the value stored in errno is printed as
// a decimal number.  For other conversions, the result is
// undefined.
void	spec_flag_alt_form(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);

// The converted value is to be left adjusted on the field
// boundary.  (The default is right justification.)  The
// converted value is padded on the right with blanks, rather
// than on the left with blanks or zeros.  A - overrides a 0
// if both are given.
void	spec_flag_left_align_override(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);

// The value should be zero padded.  For d, i, o, u, x, X, a,
// A, e, E, f, F, g, and G conversions, the converted value is
// padded on the left with zeros rather than blanks.  If the 0
// and - flags both appear, the 0 flag is ignored.  If a
// precision is given with an integer conversion (d, i, o, u,
// x, and X), the 0 flag is ignored.  For other conversions,
// the behavior is undefined.
void	spec_flag_zero_pad(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);

// (a space) A blank should be left before a positive number
// (or empty string) produced by a signed conversion.
void	spec_flag_space(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);

// A sign (+ or -) should always be placed before a number
// produced by a signed conversion.  By default, a sign is
// used only for negative numbers.  A + overrides a space if
// both are used.
void	spec_flag_plus_override(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
#endif