/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:36:40 by vtian             #+#    #+#             */
/*   Updated: 2025/06/30 22:56:22 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H
# define UCHAR_T unsigned char
# define CHAR_T char
# include <stdarg.h>
# include <stdio.h>

typedef struct s_spec
{
	/* Flag for negative number.  */
	int			is_negative;
	long long	number;
	int			base;
	/* Pointer to argument string.  */
	CHAR_T		*string;
	/* Alternate format.  */
	int			alt;
	/* Use space prefix if no sign is needed.  */
	int			space;
	/* Left-justify output.  */
	int			left;
	/* Always begin with plus or minus sign.  */
	int			showsign;
	/* Print	numbers according grouping rules.  */
	int			group;
	/* Argument is long double/ long long int.  */
	int			is_long_double;
	/* Argument is short int.  */
	int			is_short;
	/* Argument is long int.  */
	int			is_long;
	/* Argument is promoted (unsigned) char.  */
	int			is_char;
	/* Width of output; 0 means none specified.  */
	int			width;
	/* Precision of output; -1 means none specified.  */
	int			prec;
	/* This flag is set by the 'I' modifier and selects the use of the
	`outdigits' as determined by the current locale.  */
	int			use_outdigits;
	/* Padding character.  */
	UCHAR_T		pad;
	CHAR_T		spec;
}	t_spec;

typedef struct s_state
{
	// Place to accumulate the result.
	int				done;
	// Current character in format string.
	const UCHAR_T	*f;
	// UNUSED End of leading constant string.
	const UCHAR_T	*lead_str_end;
	// Points to next format specifier.
	const UCHAR_T	*end_of_spec;
	// Buffer intermediate results.
	// CHAR_T			work_buffer[1000];
	// CHAR_T			*workstart;
	// CHAR_T			*workend;
	// We have to save the original argument pointer.
	va_list			ap_save;
	// Count number of specifiers we already processed.
	int				nspecs_done;
	// NON LIBC Error propagation bit.
	int				err;
	t_spec			*spec;
}	t_state;

typedef enum dispatch_step
{
	NONE,
	STEP_FLAGS_WIDTH_PRECISION_FORMAT,
	STEP_PRECISION_FORMAT,
	STEP_FORMAT
}	t_dispatch_step;

void	pad(FILE *s, t_state *state, UCHAR_T *string, int width);

void	pad_zero(FILE *s, t_state *state, UCHAR_T *string, int width);

void	outstring(FILE *s, int *done, const CHAR_T *string, int len);

char	*ft_utoa(unsigned int n, int base);

void	spec_conversion_char(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_conversion_string(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_conversion_int(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_conversion_pointer(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_conversion_uint(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_conversion_hex(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
void	spec_conversion_percent(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);

// NONLIBC takes all the arguements of vfprintf
// used in place of libc's printf goto implementation
void	dispatch(FILE *s, va_list ap, t_state *state);

typedef void (*	t_dispatch_handler)(FILE *s, va_list ap, t_state *state,
			t_dispatch_step *table);
#endif