/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:11:30 by vtian             #+#    #+#             */
/*   Updated: 2025/07/04 00:14:13 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H 
# include <stdarg.h>
# include <stdio.h>

// Write formatted output to stdout.
// THIS IS AN UNBUFFERED REWRITE.
// This function is a possible cancellation point and therefore not
// marked with THROW.
int	ft_printf(char const *str, ...);

// Write formatted output to S from arguement list ARG.
// THIS IS AN UNBUFFERED REWRITE.
// This function is a possible cancellation point and therefore not
// marked with THROW.
int	ft_vfprintf(FILE *s, const char *format, va_list ap);
#endif