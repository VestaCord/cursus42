/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:08:42 by vtian             #+#    #+#             */
/*   Updated: 2025/06/21 00:47:47 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include "stdlib.h"
# ifndef ULIMIT_OPEN_FILES
#  define ULIMIT_OPEN_FILES 1024
# endif
// Writes n zero-valued bytes to the string s. If n is zero, ft_bzero() does
// nothing.
void	ft_bzero(void *s, size_t n);

// Allocates contiguous memory for an array of count elements of size bytes,
// each, and initializes the memory to zero. Returns a pointer to the allocated
// memory.
void	*ft_calloc(size_t count, size_t size);

// Locates the first occurrence of c (converted to a char) in the string pointed
// to by s. The terminating null byte is considered part of the string.
char	*ft_strchr(const char *s, int c);

// Allocates memory (using malloc(3)) and returns a
// new string, which is the result of concatenating
// 's1' and 's2'.
char	*ft_strjoin(char const *s1, char const *s2);

// Calculates the length of the string s, excluding the terminating null byte
// ('\0').
size_t	ft_strlen(const char *s);

// Write a function that returns a line read from a file descriptor
// Returns Read line or NULL if there is
// nothing else to read, or an error occurred
// Allowed external funcs: read, malloc, free
char	*get_next_line(int fd);
#endif